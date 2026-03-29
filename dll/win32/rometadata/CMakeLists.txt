
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(rometadata.dll rometadata.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/rometadata_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/rometadata.def)

add_library(rometadata SHARED ${SOURCE})
set_module_type(rometadata win32dll ENTRYPOINT 0)
target_link_libraries(rometadata wine wine_dll_canunload)
add_importlibs(rometadata combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET rometadata DESTINATION reactos/system32 FOR all)
