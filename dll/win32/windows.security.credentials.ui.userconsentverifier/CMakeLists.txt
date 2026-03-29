
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.security.credentials.ui.userconsentverifier.dll windows.security.credentials.ui.userconsentverifier.spec ADD_IMPORTLIB)
add_idl_headers(windows.security.credentials.ui.userconsentverifier_idlheader provider.idl)

list(APPEND SOURCE
    async.c
    main.c
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.security.credentials.ui.userconsentverifier_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.security.credentials.ui.userconsentverifier.def)

add_library(windows.security.credentials.ui.userconsentverifier SHARED ${SOURCE})
add_dependencies(windows.security.credentials.ui.userconsentverifier windows.security.credentials.ui.userconsentverifier_idlheader)
set_module_type(windows.security.credentials.ui.userconsentverifier win32dll ENTRYPOINT 0)
target_link_libraries(windows.security.credentials.ui.userconsentverifier wine wine_dll_canunload)
add_importlibs(windows.security.credentials.ui.userconsentverifier combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.security.credentials.ui.userconsentverifier DESTINATION reactos/system32 FOR all)
