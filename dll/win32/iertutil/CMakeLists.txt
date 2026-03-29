
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(iertutil.dll iertutil.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/iertutil_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/iertutil.def)

add_library(iertutil SHARED ${SOURCE})
set_module_type(iertutil win32dll ENTRYPOINT 0)
target_link_libraries(iertutil wine wine_dll_canunload)
add_importlibs(iertutil combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET iertutil DESTINATION reactos/system32 FOR all)
