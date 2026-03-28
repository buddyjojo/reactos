
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.devices.enumeration.dll windows.devices.enumeration.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    access.c
    event_handlers.c
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.devices.enumeration_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.devices.enumeration.def)

add_library(windows.devices.enumeration SHARED ${SOURCE})
set_module_type(windows.devices.enumeration win32dll ENTRYPOINT 0)
target_link_libraries(windows.devices.enumeration wine wine_dll_canunload uuid)
add_importlibs(windows.devices.enumeration combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.devices.enumeration DESTINATION reactos/system32 FOR all)
