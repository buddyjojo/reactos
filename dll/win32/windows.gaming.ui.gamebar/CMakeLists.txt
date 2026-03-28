
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.gaming.ui.gamebar.dll windows.gaming.ui.gamebar.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.gaming.ui.gamebar_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.gaming.ui.gamebar.def)

add_library(windows.gaming.ui.gamebar SHARED ${SOURCE})
set_module_type(windows.gaming.ui.gamebar win32dll ENTRYPOINT 0)
target_link_libraries(windows.gaming.ui.gamebar wine wine_dll_canunload uuid)
add_importlibs(windows.gaming.ui.gamebar combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.gaming.ui.gamebar DESTINATION reactos/system32 FOR all)
