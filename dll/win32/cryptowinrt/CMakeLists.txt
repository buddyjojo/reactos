
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(cryptowinrt.dll cryptowinrt.spec ADD_IMPORTLIB)
add_idl_headers(cryptowinrt_idlheader provider.idl)

list(APPEND SOURCE
    async.c
    credentials.c
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/cryptowinrt_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/cryptowinrt.def)

add_library(cryptowinrt SHARED ${SOURCE})
add_dependencies(cryptowinrt cryptowinrt_idlheader)
set_module_type(cryptowinrt win32dll ENTRYPOINT 0)
target_link_libraries(cryptowinrt wine wine_dll_canunload uuid)
add_importlibs(cryptowinrt combase ucrtbase bcrypt kernel32 ntdll )
add_cd_file(TARGET cryptowinrt DESTINATION reactos/system32 FOR all)
