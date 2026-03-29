
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.networking.connectivity.dll windows.networking.connectivity.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    network_information.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.networking.connectivity_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.networking.connectivity.def)

add_library(windows.networking.connectivity SHARED ${SOURCE})
set_module_type(windows.networking.connectivity win32dll ENTRYPOINT 0)
target_link_libraries(windows.networking.connectivity wine wine_dll_register wine_dll_canunload)
add_importlibs(windows.networking.connectivity combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.networking.connectivity DESTINATION reactos/system32 FOR all)
