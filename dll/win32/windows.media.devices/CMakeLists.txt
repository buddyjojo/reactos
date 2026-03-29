
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.media.devices.dll windows.media.devices.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.media.devices_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.media.devices.def)

add_library(windows.media.devices SHARED ${SOURCE})
set_module_type(windows.media.devices win32dll ENTRYPOINT 0)
target_link_libraries(windows.media.devices wine wine_dll_canunload)
add_importlibs(windows.media.devices combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.media.devices DESTINATION reactos/system32 FOR all)
