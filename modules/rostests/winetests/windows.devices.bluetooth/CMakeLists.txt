
add_definitions(-DWINETEST_USE_DBGSTR_HSTRING)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)

add_executable(windows.devices.bluetooth_winetest bluetooth.c)
target_compile_definitions(windows.devices.bluetooth_winetest PRIVATE STANDALONE __WINESRC__)
set_module_type(windows.devices.bluetooth_winetest win32cui)
add_importlibs(windows.devices.bluetooth_winetest windows.devices.bluetooth combase msvcrt kernel32)
add_rostests_file(TARGET windows.devices.bluetooth_winetest)
