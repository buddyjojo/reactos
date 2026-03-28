
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(appxdeploymentclient.dll appxdeploymentclient.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    package.c
    ${CMAKE_CURRENT_BINARY_DIR}/appxdeploymentclient_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/appxdeploymentclient.def)

add_library(appxdeploymentclient SHARED ${SOURCE})
set_module_type(appxdeploymentclient win32dll ENTRYPOINT 0)
target_link_libraries(appxdeploymentclient wine wine_dll_canunload)
add_importlibs(appxdeploymentclient combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET appxdeploymentclient DESTINATION reactos/system32 FOR all)
