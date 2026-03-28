
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(hvsimanagementapi.dll hvsimanagementapi.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    host.c
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/hvsimanagementapi_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/hvsimanagementapi.def)

add_library(hvsimanagementapi SHARED ${SOURCE})
set_module_type(hvsimanagementapi win32dll ENTRYPOINT 0)
target_link_libraries(hvsimanagementapi wine wine_dll_canunload)
add_importlibs(hvsimanagementapi combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET hvsimanagementapi DESTINATION reactos/system32 FOR all)
