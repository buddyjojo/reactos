
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.applicationmodel.dll windows.applicationmodel.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    package.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.applicationmodel_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.applicationmodel.def)

add_library(windows.applicationmodel SHARED ${SOURCE})
set_module_type(windows.applicationmodel win32dll ENTRYPOINT 0)
target_link_libraries(windows.applicationmodel wine wine_dll_canunload)
add_importlibs(windows.applicationmodel combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.applicationmodel DESTINATION reactos/system32 FOR all)
