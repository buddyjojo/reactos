
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.security.authentication.onlineid.dll windows.security.authentication.onlineid.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    authenticator.c
    main.c
    ticket.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.security.authentication.onlineid_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.security.authentication.onlineid.def)

add_library(windows.security.authentication.onlineid SHARED ${SOURCE})
set_module_type(windows.security.authentication.onlineid win32dll ENTRYPOINT 0)
target_link_libraries(windows.security.authentication.onlineid wine wine_dll_canunload)
add_importlibs(windows.security.authentication.onlineid combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.security.authentication.onlineid DESTINATION reactos/system32 FOR all)
