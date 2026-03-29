
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(wintypes.dll wintypes.spec ADD_IMPORTLIB)
add_idl_headers(wintypes_idlheader wintypes_private.idl)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/wintypes_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/wintypes.def)

add_library(wintypes SHARED ${SOURCE})
add_dependencies(wintypes wintypes_idlheader)
set_module_type(wintypes win32dll ENTRYPOINT 0)
target_link_libraries(wintypes wine wine_dll_canunload)
add_importlibs(wintypes combase ucrtbase msvcrt kernel32 ntdll )
add_cd_file(TARGET wintypes DESTINATION reactos/system32 FOR all)
