
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(geolocation.dll geolocation.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/geolocation_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/geolocation.def)

add_library(geolocation SHARED ${SOURCE})
set_module_type(geolocation win32dll ENTRYPOINT 0)
target_link_libraries(geolocation wine wine_dll_canunload uuid)
add_importlibs(geolocation combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET geolocation DESTINATION reactos/system32 FOR all)
