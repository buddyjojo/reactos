/*
 * PROJECT:     Universal serial bus modem driver
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     USB modem driver usb functions.
 * COPYRIGHT:   Copyright 2022 Vadim Galyant <vgal@rambler.ru>
 */

/* INCLUDES ******************************************************************/

#include "usbser.h"

//#define NDEBUG
#include <debug.h>

/* DATA ***********************************************************************/

/* GLOBALS ********************************************************************/

/* FUNCTIONS *****************************************************************/

NTSTATUS
NTAPI
CallUSBD(IN PDEVICE_OBJECT DeviceObject,
         IN PURB Urb)
{
    PUSBSER_DEVICE_EXTENSION Extension;
    PIRP Irp;
    NTSTATUS Status;
    PIO_STACK_LOCATION IoStack;
    KEVENT Event;
    LARGE_INTEGER Timeout;

    DPRINT("CallUSBD: DeviceObject %p\n", DeviceObject);
    PAGED_CODE();

    KeInitializeEvent(&Event, SynchronizationEvent, FALSE);

    Extension = DeviceObject->DeviceExtension;

    Irp = IoAllocateIrp(Extension->LowerDevice->StackSize, FALSE);
    if (!Irp)
    {
        DPRINT1("CallUSBD: STATUS_INSUFFICIENT_RESOURCES\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    IoStack = IoGetNextIrpStackLocation(Irp);
    IoStack->MajorFunction = IRP_MJ_INTERNAL_DEVICE_CONTROL;
    IoStack->Parameters.DeviceIoControl.IoControlCode = IOCTL_INTERNAL_USB_SUBMIT_URB;
    IoStack->Parameters.Others.Argument1 = Urb;

    IoSetCompletionRoutine(Irp, UsbSerSyncCompletion, &Event, TRUE, TRUE, TRUE);

    Status = IoCallDriver(Extension->LowerDevice, Irp);
    if (Status != STATUS_PENDING)
    {
        goto Exit;
    }

    /* Set timeout 30 sec */
    Timeout.QuadPart = (30 * 1000) * -10000;

    Status = KeWaitForSingleObject(&Event, Executive, KernelMode, FALSE, &Timeout);
    if (Status != STATUS_TIMEOUT)
    {
        Status = Irp->IoStatus.Status;
        goto Exit;
    }

    /* End of timeout ... cancel this IRP */
    Status = STATUS_IO_TIMEOUT;
    IoCancelIrp(Irp);
    KeWaitForSingleObject(&Event, Executive, KernelMode, FALSE, NULL);

Exit:

    IoFreeIrp(Irp);
    return Status;
}

NTSTATUS
NTAPI
GetDeviceDescriptor(IN PDEVICE_OBJECT DeviceObject)
{
    PUSBSER_DEVICE_EXTENSION Extension;
    struct _URB_CONTROL_DESCRIPTOR_REQUEST * Urb;
    PUSB_DEVICE_DESCRIPTOR Descriptor;
    PUSB_DEVICE_DESCRIPTOR OldDescriptor;
    KIRQL Irql;
    NTSTATUS Status;

    DPRINT("GetDeviceDescriptor: DeviceObject %p\n", DeviceObject);

    Extension = DeviceObject->DeviceExtension;
    Urb = ExAllocatePoolWithTag(NonPagedPool, sizeof(*Urb), USBSER_TAG);
    if (!Urb)
    {
        DPRINT1("GetDeviceDescriptor: STATUS_INSUFFICIENT_RESOURCES\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Descriptor = ExAllocatePoolWithTag(NonPagedPool, sizeof(*Descriptor), USBSER_TAG);
    if (!Descriptor)
    {
        DPRINT1("GetDeviceDescriptor: STATUS_INSUFFICIENT_RESOURCES\n");
        ExFreePoolWithTag(Urb, USBSER_TAG);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Urb->Hdr.Function = URB_FUNCTION_GET_DESCRIPTOR_FROM_DEVICE;
    Urb->Hdr.Length = sizeof(*Urb);

    Urb->DescriptorType = USB_DEVICE_DESCRIPTOR_TYPE;
    Urb->TransferBufferLength = sizeof(*Descriptor);
    Urb->TransferBuffer = Descriptor;
    Urb->TransferBufferMDL = NULL;

    Urb->Index = 0;
    Urb->LanguageId = 0;
    Urb->UrbLink = NULL;

    Status = CallUSBD(DeviceObject, (PURB)Urb);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("GetDeviceDescriptor: Status %X\n", Status);

        if (Descriptor)
            ExFreePoolWithTag(Descriptor, USBSER_TAG);

        ExFreePoolWithTag(Urb, USBSER_TAG);

        return Status;
    }

    OldDescriptor = NULL;

    KeAcquireSpinLock(&Extension->SpinLock, &Irql);
    if (Extension->DeviceDescriptor)
        OldDescriptor = Extension->DeviceDescriptor;
    Extension->DeviceDescriptor = Descriptor;
    KeReleaseSpinLock(&Extension->SpinLock, Irql);

    if (OldDescriptor)
        ExFreePoolWithTag(OldDescriptor, USBSER_TAG);

    ExFreePoolWithTag(Urb, USBSER_TAG);

    return Status;
}

NTSTATUS
NTAPI
SelectInterface(IN PDEVICE_OBJECT DeviceObject,
                IN PUSB_CONFIGURATION_DESCRIPTOR Descriptor)
{
    PUSBSER_DEVICE_EXTENSION Extension;
    PUSBD_INTERFACE_INFORMATION Interface;
    PUSBD_INTERFACE_INFORMATION InterfaceArray[2];
    PUSB_INTERFACE_DESCRIPTOR iDesc;
    PURB Urb = NULL;
    PVOID NotifyBuffer;
    PVOID ReadBuffer;
    PVOID RxBuffer;
    PVOID OldReadBuffer;
    PVOID OldRxBuffer;
    PVOID OldNotifyBuffer;
    ULONG ix;
    USHORT Size;
    BOOLEAN InterfaceFound = FALSE;
    KIRQL Irql;
    NTSTATUS Status;

    DPRINT("SelectInterface: DeviceObject %p, Descriptor %p\n", DeviceObject, Descriptor);

    Urb = USBD_CreateConfigurationRequest(Descriptor, &Size);
    if (!Urb)
    {
        DPRINT1("SelectInterface: STATUS_INSUFFICIENT_RESOURCES\n");
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto Exit;
    }

    Interface = &Urb->UrbSelectConfiguration.Interface;

    for (ix = 0; ix < Descriptor->bNumInterfaces; ix++)
    {
        iDesc = USBD_ParseConfigurationDescriptor(Descriptor, ix, 0);

        Interface->Length = (sizeof(USBD_INTERFACE_INFORMATION) +
                            (sizeof(USBD_PIPE_INFORMATION) * (iDesc->bNumEndpoints - 1)));

        Interface->InterfaceNumber = iDesc->bInterfaceNumber;
        Interface->AlternateSetting = iDesc->bAlternateSetting;

        InterfaceArray[ix] = Interface;

        for (ix = 0; ix < Interface->NumberOfPipes; ix++)
        {
            if (USB_ENDPOINT_DIRECTION_IN(Interface->Pipes[ix].EndpointAddress))
            {
                if (Interface->Pipes[ix].PipeType == UsbdPipeTypeBulk)
                {
                    Interface->Pipes[ix].MaximumTransferSize = 0x1000;
                }
            }
            else if (Interface->Pipes[ix].PipeType == UsbdPipeTypeBulk)
            {
                Interface->Pipes[ix].MaximumTransferSize = 0x2000;
            }
        }

        Interface = (PUSBD_INTERFACE_INFORMATION)((ULONG_PTR)Interface + Interface->Length);
    }

    Urb->UrbHeader.Function = URB_FUNCTION_SELECT_CONFIGURATION;
    Urb->UrbHeader.Length = Size;
    Urb->UrbSelectConfiguration.ConfigurationDescriptor = Descriptor;

    Status = CallUSBD(DeviceObject, (PURB)Urb);
    if (Status != STATUS_SUCCESS)
    {
        DPRINT1("SelectInterface: Status %X\n", Status);
        ExFreePoolWithTag(Urb, USBSER_TAG);
        return Status;
    }

    Extension = DeviceObject->DeviceExtension;
    Extension->ConfigurationHandle = Urb->UrbSelectConfiguration.ConfigurationHandle;

    for (ix = 0; ix < Descriptor->bNumInterfaces; ix++)
    {
        Interface = InterfaceArray[ix];

        if (Interface->Class == USB_DEVICE_CLASS_COMMUNICATIONS)//2
        {
            DPRINT1("SelectInterface: find interface number %X\n", Interface->InterfaceNumber);
            InterfaceFound = TRUE;
            Extension->InterfaceNumber = Interface->InterfaceNumber;
        }

        for (ix = 0; ix < Interface->NumberOfPipes; ix++)
        {
            if (USB_ENDPOINT_DIRECTION_IN(Interface->Pipes[ix].EndpointAddress))
            {
                if (Interface->Pipes[ix].PipeType == UsbdPipeTypeBulk)
                {
                    Extension->RxBufferSize = RxBufferSize;

                    if (RxBufferSize)
                        RxBuffer = ExAllocatePoolWithTag(NonPagedPool, RxBufferSize, USBSER_TAG);
                    else
                        RxBuffer = NULL;

                    NotifyBuffer = ExAllocatePoolWithTag(NonPagedPool, sizeof(USBSER_CDC_NOTIFICATION), USBSER_TAG);
                    ReadBuffer = ExAllocatePoolWithTag(NonPagedPool, 0x1000, USBSER_TAG);

                    KeAcquireSpinLock(&Extension->SpinLock, &Irql);

                    Extension->DataInPipeHandle = Interface->Pipes[ix].PipeHandle;

                    if (Extension->NotifyBuffer)
                        OldNotifyBuffer = Extension->NotifyBuffer;
                    else
                        OldNotifyBuffer = NULL;

                    if (Extension->RxBuffer)
                        OldRxBuffer = Extension->RxBuffer;
                    else
                        OldRxBuffer = NULL;

                    if (Extension->ReadBuffer)
                        OldReadBuffer = Extension->ReadBuffer;
                    else
                        OldReadBuffer = NULL;

                    Extension->CharsInReadBuffer = 0;
                    Extension->ReadBufferOffset = 0;

                    Extension->RxBuffer = RxBuffer;

                    Extension->ReadBuffer = ReadBuffer;
                    Extension->NotifyBuffer = NotifyBuffer;

                    KeReleaseSpinLock(&Extension->SpinLock, Irql);

                    if (OldNotifyBuffer) ExFreePoolWithTag(OldNotifyBuffer, USBSER_TAG);
                    if (OldRxBuffer) ExFreePoolWithTag(OldRxBuffer, USBSER_TAG);
                    if (OldReadBuffer) ExFreePoolWithTag(OldReadBuffer, USBSER_TAG);
                }
                else if (Interface->Pipes[ix].PipeType == UsbdPipeTypeInterrupt)
                {
                    Extension->NotifyPipeHandle = Interface->Pipes[ix].PipeHandle;
                }
            }
            else if (Interface->Pipes[ix].PipeType == UsbdPipeTypeBulk)
            {
                Extension->DataOutPipeHandle = Interface->Pipes[ix].PipeHandle;
            }
        }
    }

Exit:

    if (Urb)
        ExFreePoolWithTag(Urb, USBSER_TAG);

    if (!InterfaceFound)
    {
        DPRINT1("SelectInterface: interface not found!\n");
        Status = STATUS_NO_SUCH_DEVICE;
    }

    return Status;
}

NTSTATUS
NTAPI
ConfigureDevice(IN PDEVICE_OBJECT DeviceObject)
{
    PUSBSER_DEVICE_EXTENSION Extension;
    struct _URB_CONTROL_DESCRIPTOR_REQUEST * Urb;
    PUSB_CONFIGURATION_DESCRIPTOR Descriptor;
    ULONG Length;
    UCHAR Index;
    NTSTATUS Status;

    DPRINT("ConfigureDevice: DeviceObject %p\n", DeviceObject);
    PAGED_CODE();

    Urb = ExAllocatePoolWithTag(NonPagedPool, sizeof(*Urb), USBSER_TAG);
    if (!Urb)
    {
        DPRINT1("ConfigureDevice: Status %X\n", STATUS_INSUFFICIENT_RESOURCES);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Extension = DeviceObject->DeviceExtension;
    if (!Extension->DeviceDescriptor->bNumConfigurations)
    {
        DPRINT1("ConfigureDevice: bNumConfigurations is 0\n");
        goto Exit;
    }

    DPRINT("ConfigureDevice: bNumConfigurations %X\n", Extension->DeviceDescriptor->bNumConfigurations);

    Length = sizeof(USB_CONFIGURATION_DESCRIPTOR) + 0x100; // ?

    for (Index = 0;
         Index < Extension->DeviceDescriptor->bNumConfigurations;
        )
    {
        DPRINT("ConfigureDevice: Index %X\n", Index);

        Descriptor = ExAllocatePoolWithTag(NonPagedPool, Length, USBSER_TAG);
        if (!Descriptor)
        {
            DPRINT1("ConfigureDevice: STATUS_INSUFFICIENT_RESOURCES\n");
            Status = STATUS_INSUFFICIENT_RESOURCES;
            Index++;
            continue;
        }

        Urb->Hdr.Function = URB_FUNCTION_GET_DESCRIPTOR_FROM_DEVICE;
        Urb->Hdr.Length = sizeof(*Urb);

        Urb->DescriptorType = USB_CONFIGURATION_DESCRIPTOR_TYPE;
        Urb->TransferBufferLength = Length;
        Urb->TransferBuffer = Descriptor;
        Urb->TransferBufferMDL = NULL;

        Urb->Index = Index;
        Urb->LanguageId = 0;
        Urb->UrbLink = NULL;

        Status = CallUSBD(DeviceObject, (PURB)Urb);
        if (Urb->TransferBufferLength && Length < Descriptor->wTotalLength)
        {
            DPRINT("ConfigureDevice: Length %X, wTotalLength %X\n", Length, Descriptor->wTotalLength);
            Length = Descriptor->wTotalLength;
            ExFreePoolWithTag(Descriptor, USBSER_TAG);
            continue;
        }

        if (NT_SUCCESS(Status))
        {
            Status = SelectInterface(DeviceObject, Descriptor);
        }
        else
        {
            DPRINT1("ConfigureDevice: Status %X\n", Status);
        }

        ExFreePoolWithTag(Descriptor, USBSER_TAG);

        if (NT_SUCCESS(Status))
        {
            break;
        }

        DPRINT1("ConfigureDevice: Status %X\n", Status);

        Index++;
    }

Exit:

    ExFreePoolWithTag(Urb, USBSER_TAG);
    return Status;
}

NTSTATUS
NTAPI
ClassVendorCommand(IN PDEVICE_OBJECT DeviceObject,
                   IN UCHAR Request,
                   IN USHORT Value,
                   IN USHORT Index,
                   IN PVOID TransferBuffer,
                   IN OUT ULONG * OutLength,
                   IN ULONG Direction,
                   IN BOOLEAN IsClassFunction)
{
    struct _URB_CONTROL_VENDOR_OR_CLASS_REQUEST * Urb;
    ULONG Length = 0;
    NTSTATUS Status;

    DPRINT("ClassVendorCommand: Request %X\n", Request);
    PAGED_CODE();

    if (OutLength)
        Length = *OutLength;

    Urb = ExAllocatePoolWithTag(NonPagedPool, sizeof(*Urb), USBSER_TAG);
    if (!Urb)
    {
        DPRINT1("ClassVendorCommand: STATUS_INSUFFICIENT_RESOURCES\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Urb->Hdr.Length = sizeof(*Urb);

    Urb->TransferBufferLength = Length;
    Urb->TransferBufferMDL = NULL;
    Urb->RequestTypeReservedBits = 0;
    Urb->UrbLink = NULL;

    if (IsClassFunction)
        Urb->Hdr.Function = URB_FUNCTION_CLASS_INTERFACE;
    else
        Urb->Hdr.Function = URB_FUNCTION_VENDOR_DEVICE;

    Urb->TransferBuffer = TransferBuffer;
    Urb->Request = Request;
    Urb->Value = Value;
    Urb->Index = Index;
    Urb->TransferFlags = (Direction == USBD_TRANSFER_DIRECTION_IN);

    Status = CallUSBD(DeviceObject, (PURB)Urb);

    if (OutLength)
        *OutLength = Urb->TransferBufferLength;

    ExFreePoolWithTag(Urb, USBSER_TAG);

    return Status;
}

NTSTATUS
NTAPI
ResetDevice(IN PDEVICE_OBJECT DeviceObject)
{
    PUSBSER_DEVICE_EXTENSION Extension;
    KIRQL Irql;

    DPRINT("ResetDevice: DeviceObject %p\n", DeviceObject);
    PAGED_CODE();

    GetLineControlAndBaud(DeviceObject);

    Extension = DeviceObject->DeviceExtension;

    KeAcquireSpinLock(&Extension->SpinLock, &Irql);
    Extension->SupportedBauds = 420720; // ?
    KeReleaseSpinLock(&Extension->SpinLock, Irql);

    return STATUS_SUCCESS;
}

/* EOF */
