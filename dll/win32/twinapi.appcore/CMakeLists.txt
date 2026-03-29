
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502 -D_CRT_NON_CONFORMING_SWPRINTFS)
add_definitions(-D_WIN32_WINNT=0x600 -D_CONTRACT_GEN)
include_directories(BEFORE ${REACTOS_SOURCE_DIR}/sdk/include/wine)

spec2def(twinapi.appcore.dll twinapi.appcore.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    advertising_manager.c
    analytics_info.c
    client_device_information.c
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/twinapi.appcore_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/twinapi.appcore.def)

add_library(twinapi.appcore SHARED ${SOURCE})
set_module_type(twinapi.appcore win32dll ENTRYPOINT 0)
target_link_libraries(twinapi.appcore wine wine_dll_canunload)
add_importlibs(twinapi.appcore combase ucrtbase advapi32 kernel32 ntdll )
add_cd_file(TARGET twinapi.appcore DESTINATION reactos/system32 FOR all)
