
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.system.profile.systemmanufacturers.dll windows.system.profile.systemmanufacturers.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.system.profile.systemmanufacturers_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.system.profile.systemmanufacturers.def)

add_library(windows.system.profile.systemmanufacturers MODULE ${SOURCE})
set_module_type(windows.system.profile.systemmanufacturers win32dll ENTRYPOINT 0)
add_idl_reg_scripts(windows.system.profile.systemmanufacturers winrt classes.idl)
target_link_libraries(windows.system.profile.systemmanufacturers wine wine_dll_register wine_dll_canunload)
add_importlibs(windows.system.profile.systemmanufacturers combase oleaut32 ucrtbase kernel32 ntdll)
add_cd_file(TARGET windows.system.profile.systemmanufacturers DESTINATION reactos/system32 FOR all)
set_wine_module_FIXME(windows.system.profile.systemmanufacturers) # CORE-5743: ???
