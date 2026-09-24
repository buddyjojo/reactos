
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.media.mediacontrol.dll windows.media.mediacontrol.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.media.mediacontrol_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.media.mediacontrol.def)

add_library(windows.media.mediacontrol MODULE ${SOURCE})
set_module_type(windows.media.mediacontrol win32dll ENTRYPOINT 0)
add_idl_reg_scripts(windows.media.mediacontrol winrt classes.idl)
target_link_libraries(windows.media.mediacontrol wine wine_dll_register wine_dll_canunload)
add_importlibs(windows.media.mediacontrol combase ucrtbase kernel32 ntdll)
add_cd_file(TARGET windows.media.mediacontrol DESTINATION reactos/system32 FOR all)
set_wine_module_FIXME(windows.media.mediacontrol) # CORE-5743: ???
