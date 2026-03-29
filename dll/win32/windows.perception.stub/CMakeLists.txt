
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.perception.stub.dll windows.perception.stub.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    holographicspace.c
    main.c
    observer.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.perception.stub_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.perception.stub.def)

add_library(windows.perception.stub SHARED ${SOURCE})
set_module_type(windows.perception.stub win32dll ENTRYPOINT 0)
target_link_libraries(windows.perception.stub wine wine_dll_canunload)
add_importlibs(windows.perception.stub combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.perception.stub DESTINATION reactos/system32 FOR all)
