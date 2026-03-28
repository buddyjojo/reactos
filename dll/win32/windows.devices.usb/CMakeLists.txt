
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502 -D_CRT_NON_CONFORMING_SWPRINTFS)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.devices.usb.dll windows.devices.usb.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    usbdevice.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.devices.usb_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.devices.usb.def)

add_library(windows.devices.usb SHARED ${SOURCE})
set_module_type(windows.devices.usb win32dll ENTRYPOINT 0)
target_link_libraries(windows.devices.usb wine wine_dll_canunload)
add_importlibs(windows.devices.usb combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.devices.usb DESTINATION reactos/system32 FOR all)
