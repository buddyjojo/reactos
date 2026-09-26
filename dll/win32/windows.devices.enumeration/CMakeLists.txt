
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.devices.enumeration.dll windows.devices.enumeration.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    access.c
    main.c
    event_handlers.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.devices.enumeration_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.devices.enumeration.def)

add_library(windows.devices.enumeration MODULE ${SOURCE})
set_module_type(windows.devices.enumeration win32dll ENTRYPOINT 0)
add_idl_reg_scripts(windows.devices.enumeration winrt classes.idl)
target_link_libraries(windows.devices.enumeration wine wine_dll_register wine_dll_canunload uuid)
add_importlibs(windows.devices.enumeration combase ucrtbase kernel32 ntdll)
add_cd_file(TARGET windows.devices.enumeration DESTINATION reactos/system32 FOR all)
set_wine_module_FIXME(windows.devices.enumeration) # CORE-5743: ???
