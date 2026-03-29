
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600 -D_USE_MATH_DEFINES)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.gaming.input.dll windows.gaming.input.spec ADD_IMPORTLIB)
add_idl_headers(windows.gaming.input_idlheader provider.idl)

list(APPEND SOURCE
    async.c
    condition_effect.c
    constant_effect.c
    controller.c
    event_handlers.c
    force_feedback.c
    gamepad.c
    main.c
    manager.c
    periodic_effect.c
    provider.c
    provider.idl
    racing_wheel.c
    ramp_effect.c
    vector.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.gaming.input_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.gaming.input.def)

add_library(windows.gaming.input SHARED ${SOURCE})
add_dependencies(windows.gaming.input windows.gaming.input_idlheader)
set_module_type(windows.gaming.input win32dll ENTRYPOINT 0)
target_link_libraries(windows.gaming.input wine wine_dll_canunload dinput_data_formats uuid)
add_importlibs(windows.gaming.input combase user32 dinput8 setupapi hid ucrtbase msvcrt kernel32 ntdll )
add_cd_file(TARGET windows.gaming.input DESTINATION reactos/system32 FOR all)
