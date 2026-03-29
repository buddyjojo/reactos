
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(threadpoolwinrt.dll threadpoolwinrt.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/threadpoolwinrt_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/threadpoolwinrt.def)

add_library(threadpoolwinrt SHARED ${SOURCE})
set_module_type(threadpoolwinrt win32dll ENTRYPOINT 0)
target_link_libraries(threadpoolwinrt wine wine_dll_canunload uuid)
add_importlibs(threadpoolwinrt combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET threadpoolwinrt DESTINATION reactos/system32 FOR all)
