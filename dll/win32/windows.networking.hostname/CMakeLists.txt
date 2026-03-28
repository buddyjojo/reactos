
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.networking.hostname.dll windows.networking.hostname.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    hostname.c
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.networking.hostname_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.networking.hostname.def)

add_library(windows.networking.hostname SHARED ${SOURCE})
set_module_type(windows.networking.hostname win32dll ENTRYPOINT 0)
target_link_libraries(windows.networking.hostname wine wine_dll_register wine_dll_canunload)
add_importlibs(windows.networking.hostname combase ucrtbase msvcrt kernel32 ntdll )
add_cd_file(TARGET windows.networking.hostname DESTINATION reactos/system32 FOR all)
