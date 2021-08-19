
add_executable(test-sdl++
    catch_main.cpp
    bits_test.cpp
    blendmode_test.cpp
    clipboard_test.cpp
    cpuinfo_test.cpp
    endian_test.cpp
    filesystem_test.cpp
    hints_test.cpp
    init_test.cpp
    log_test.cpp
    platform_test.cpp
    power_test.cpp
    scancode_test.cpp
    timer_test.cpp
    version_test.cpp
    )

target_link_libraries(test-sdl++ ${SDL2_LIBRARY})

add_test(test-sdl++ test-sdl++)
