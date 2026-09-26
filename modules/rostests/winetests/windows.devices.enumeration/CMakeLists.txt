
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)

add_executable(windows.devices.enumeration_winetest devices.c)
target_compile_definitions(windows.devices.enumeration_winetest PRIVATE STANDALONE __WINESRC__)
set_module_type(windows.devices.enumeration_winetest win32cui)
target_link_libraries(windows.devices.enumeration_winetest uuid)
add_importlibs(windows.devices.enumeration_winetest windows.devices.enumeration combase msvcrt kernel32)
add_rostests_file(TARGET windows.devices.enumeration_winetest)
