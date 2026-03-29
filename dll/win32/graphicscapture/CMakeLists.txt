
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(graphicscapture.dll graphicscapture.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    session.c
    ${CMAKE_CURRENT_BINARY_DIR}/graphicscapture_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/graphicscapture.def)

add_library(graphicscapture SHARED ${SOURCE})
set_module_type(graphicscapture win32dll ENTRYPOINT 0)
target_link_libraries(graphicscapture wine wine_dll_canunload)
add_importlibs(graphicscapture combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET graphicscapture DESTINATION reactos/system32 FOR all)
