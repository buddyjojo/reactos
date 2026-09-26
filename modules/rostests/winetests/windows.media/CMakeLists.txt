
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)

add_executable(windows.media_winetest captions.c)
target_compile_definitions(windows.media_winetest PRIVATE STANDALONE __WINESRC__)
set_module_type(windows.media_winetest win32cui)
add_importlibs(windows.media_winetest windows.media combase msvcrt kernel32)
add_rostests_file(TARGET windows.media_winetest)
