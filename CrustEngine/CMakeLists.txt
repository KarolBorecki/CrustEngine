cmake_minimum_required(VERSION 3.5.0)

project(CrustEngine VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(Inc)
add_subdirectory(extern/sdl)

add_executable(CrustEngine src/main.cpp)

target_link_libraries(CrustEngine SDL3::SDL3)