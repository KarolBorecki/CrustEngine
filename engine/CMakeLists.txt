cmake_minimum_required(VERSION 3.14)
project(CrustEngine)

include(ExternalProject)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5.0
            GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG v5.0.1
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

#set(RAYLIB_PATH ${CMAKE_BINARY_DIR}/raylib)
#ExternalProject_Add(raylib
#    GIT_REPOSITORY https://github.com/raysan5/raylib.git
#    GIT_TAG 5.0
#    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${RAYLIB_PATH}
#)
#include_directories(${RAYLIB_PATH}/include)
#link_directories(${RAYLIB_PATH}/lib)

#set(RAYLIBCPP_PATH ${CMAKE_BINARY_DIR}/raylib_cpp)
#ExternalProject_Add(raylib_cpp
#    GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
#    GIT_TAG v5.0.1
#    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${RAYLIBCPP_PATH}
#)
#include_directories(${RAYLIBCPP_PATH}/include)
#link_directories(${RAYLIBCPP_PATH}/lib)

set(EIGEN_PATH ${CMAKE_BINARY_DIR}/eigen)
ExternalProject_Add(eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EIGEN_PATH}
)
include_directories(${EIGEN_PATH}/include/eigen3)
link_directories(${EIGEN_PATH}/shared)

set(SOURCES Src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Inc)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)
add_dependencies(${PROJECT_NAME} eigen)