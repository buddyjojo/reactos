
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.globalization.dll windows.globalization.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    geographic_region.c
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.globalization_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.globalization.def)

add_library(windows.globalization SHARED ${SOURCE})
set_module_type(windows.globalization win32dll ENTRYPOINT 0)
target_link_libraries(windows.globalization wine wine_dll_canunload uuid)
add_importlibs(windows.globalization combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.globalization DESTINATION reactos/system32 FOR all)
