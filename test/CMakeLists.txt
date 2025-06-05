add_executable(
        test_sysinfo
        test_sysinfo.cpp
)

target_link_libraries(
        test_sysinfo
        sysinfo
)

target_include_directories(
        test_sysinfo
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)