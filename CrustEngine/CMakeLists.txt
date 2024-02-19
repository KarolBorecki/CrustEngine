cmake_minimum_required(VERSION 3.27)
project(CrustEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(./Inc)
include_directories(./extern/eigen)
include_directories(./extern/sdl/include)

add_executable(CrustEngine main.cpp)
