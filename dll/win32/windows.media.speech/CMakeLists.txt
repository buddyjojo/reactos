
add_definitions(-D__WINESRC__)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)
include_directories(${REACTOS_SOURCE_DIR}/include/reactos/wine)

spec2def(windows.media.speech.dll windows.media.speech.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    async.c
    event_handlers.c
    listconstraint.c
    main.c
    recognizer.c
    synthesizer.c
    vector.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.media.speech_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/windows.media.speech.def)

add_library(windows.media.speech SHARED ${SOURCE})
set_module_type(windows.media.speech win32dll ENTRYPOINT 0)
target_link_libraries(windows.media.speech wine wine_dll_canunload uuid)
add_importlibs(windows.media.speech combase ucrtbase kernel32 ntdll )
add_cd_file(TARGET windows.media.speech DESTINATION reactos/system32 FOR all)
