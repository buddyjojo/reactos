
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(dataexchange.dll dataexchange.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/dataexchange_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/dataexchange.def)

add_library(dataexchange SHARED ${SOURCE})
set_module_type(dataexchange win32dll ENTRYPOINT 0)
target_link_libraries(dataexchange wine wine_dll_canunload)
add_importlibs(dataexchange combase ucrtbase user32 kernel32 ntdll )
add_cd_file(TARGET dataexchange DESTINATION reactos/system32 FOR all)
