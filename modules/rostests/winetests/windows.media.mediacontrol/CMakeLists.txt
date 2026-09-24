
add_definitions(-DWINETEST_USE_DBGSTR_HSTRING)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)

add_executable(windows.media.mediacontrol_winetest mediacontrol.c)
target_compile_definitions(windows.media.mediacontrol_winetest PRIVATE STANDALONE __WINESRC__)
set_module_type(windows.media.mediacontrol_winetest win32cui)
add_importlibs(windows.media.mediacontrol_winetest windows.media.mediacontrol combase user32 msvcrt kernel32)
add_rostests_file(TARGET windows.media.mediacontrol_winetest)
