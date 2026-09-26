
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.devices.usb.dll windows.devices.usb.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    usbdevice.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.devices.usb_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.devices.usb.def)

add_library(windows.devices.usb MODULE ${SOURCE})
set_module_type(windows.devices.usb win32dll ENTRYPOINT 0)
add_idl_reg_scripts(windows.devices.usb winrt classes.idl)
target_link_libraries(windows.devices.usb wine wine_dll_register wine_dll_canunload)
add_importlibs(windows.devices.usb combase ucrtbase kernel32 ntdll)
add_cd_file(TARGET windows.devices.usb DESTINATION reactos/system32 FOR all)
set_wine_module_FIXME(windows.devices.usb) # CORE-5743: ???
