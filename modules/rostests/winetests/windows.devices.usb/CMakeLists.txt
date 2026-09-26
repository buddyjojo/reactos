
add_definitions(-DWINETEST_USE_DBGSTR_HSTRING)
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)

add_executable(windows.devices.usb_winetest usb.c)
target_compile_definitions(windows.devices.usb_winetest PRIVATE STANDALONE __WINESRC__)
set_module_type(windows.devices.usb_winetest win32cui)
add_importlibs(windows.devices.usb_winetest windows.devices.usb combase msvcrt kernel32)
add_rostests_file(TARGET windows.devices.usb_winetest)
