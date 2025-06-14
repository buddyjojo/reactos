
spec2def(qwave.dll qwave.spec)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/qwave_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/qwave.def)

add_library(qwave MODULE ${SOURCE})
set_module_type(qwave win32dll)
target_link_libraries(qwave wine)
add_importlibs(qwave msvcrt kernel32 ntdll)
add_cd_file(TARGET qwave DESTINATION reactos/system32 FOR all)
set_wine_module_FIXME(qwave) # CORE-5743: ??? 
