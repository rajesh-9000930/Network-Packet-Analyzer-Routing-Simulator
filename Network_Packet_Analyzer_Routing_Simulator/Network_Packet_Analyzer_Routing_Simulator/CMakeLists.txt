cmake_minimum_required(VERSION 3.16)
project(NetworkPacketAnalyzerRoutingSimulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(network_analyzer
    src/main.cpp
    src/packet_analyzer.cpp
    src/routing.cpp
)

target_include_directories(network_analyzer PRIVATE include)

if(MSVC)
    target_compile_options(network_analyzer PRIVATE /W4)
else()
    target_compile_options(network_analyzer PRIVATE -Wall -Wextra -Wpedantic)
endif()
