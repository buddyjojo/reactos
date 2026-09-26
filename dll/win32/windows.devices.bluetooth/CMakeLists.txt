
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.devices.bluetooth.dll windows.devices.bluetooth.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    bluetoothadapter.c
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.devices.bluetooth_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.devices.bluetooth.def)

add_library(windows.devices.bluetooth MODULE ${SOURCE})
set_module_type(windows.devices.bluetooth win32dll ENTRYPOINT 0)
add_idl_reg_scripts(windows.devices.bluetooth winrt classes.idl)
target_link_libraries(windows.devices.bluetooth wine wine_dll_register wine_dll_canunload)
add_importlibs(windows.devices.bluetooth combase ucrtbase kernel32 ntdll)
add_cd_file(TARGET windows.devices.bluetooth DESTINATION reactos/system32 FOR all)
set_wine_module_FIXME(windows.devices.bluetooth) # CORE-5743: ???
