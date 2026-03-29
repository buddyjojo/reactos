
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.web.dll windows.web.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    json_object.c
    json_value.c
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.web_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.web.def)

add_library(windows.web SHARED ${SOURCE})
set_module_type(windows.web win32dll ENTRYPOINT 0)
target_link_libraries(windows.web wine wine_dll_register wine_dll_canunload)
add_importlibs(windows.web combase ucrtbase msvcrt kernel32 ntdll )
add_cd_file(TARGET windows.web DESTINATION reactos/system32 FOR all)
