
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.media.dll windows.media.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    captions.c
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.media_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.media.def)

add_library(windows.media SHARED ${SOURCE})
set_module_type(windows.media win32dll ENTRYPOINT 0)
target_link_libraries(windows.media wine wine_dll_canunload)
add_importlibs(windows.media combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.media DESTINATION reactos/system32 FOR all)
