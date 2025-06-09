cmake_minimum_required(VERSION 3.20)

project(sysinfo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND SRC sysinfo.h)
if (LINUX)
    list(APPEND SRC sysinfo_linux.cpp)
elseif (APPLE)
    list(APPEND SRC sysinfo_mac.cpp)
endif()

add_library(sysinfo STATIC
    ${SRC}
)

add_subdirectory(test)
