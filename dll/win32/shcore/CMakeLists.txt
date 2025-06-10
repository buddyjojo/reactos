
spec2def(shcore.dll shcore.spec)

list(APPEND SOURCE
    main.c
    ${CMAKE_CURRENT_BINARY_DIR}/shcore_stubs.c
    )

add_library(shcore MODULE ${SOURCE})
set_module_type(shcore win32dll)
target_link_libraries(shcore wine)
add_importlibs(shcore ole32 user32 user32_vista advapi32 advapi32_vista msvcrt kernel32 ntdll)
add_cd_file(TARGET shcore DESTINATION reactos/system32 FOR all)
set_wine_module_FIXME(shcore) # CORE-5743: ???
