
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.storage.applicationdata.dll windows.storage.applicationdata.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    applicationdata.c
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.storage.applicationdata_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.storage.applicationdata.def)

add_library(windows.storage.applicationdata SHARED ${SOURCE})
set_module_type(windows.storage.applicationdata win32dll ENTRYPOINT 0)
target_link_libraries(windows.storage.applicationdata wine wine_dll_canunload)
add_importlibs(windows.storage.applicationdata combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.storage.applicationdata DESTINATION reactos/system32 FOR all)
