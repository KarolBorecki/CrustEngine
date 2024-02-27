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

# TODO review
set(SOURCES main.cpp
        inc/rendering/Library2DWrapper.h
        src/rendering/Library2DWrapper.cpp
        inc/static/Definitions.h
        inc/rendering/Renderer.h
        src/rendering/Renderer.cpp
        inc/rendering/Projector.h
        src/rendering/Projector.cpp
        src/core/Scene.cpp
        inc/core/Scene.h
        src/core/Window.cpp
        inc/core/Window.h
        src/objects/Object.cpp
        inc/objects/Object.h
        src/objects/Transform.cpp
        inc/objects/Transform.h
        inc/math/Vector3.h
        inc/scripting/Script.h
        inc/math/Matrix.h
        inc/logging/Logger.h
        inc/math/Vector4.h
        src/core/Core.cpp
        inc/core/Core.h
        src/objects/RenderObject.cpp
        inc/objects/RenderObject.h
        src/objects/Camera.cpp
        inc/objects/Camera.h
        src/objects/LightSource.cpp
        inc/objects/LightSource.h
        inc/files/MeshLoader.h
        src/files/MeshLoader.cpp
        src/math/geometry/Polygon.cpp
        inc/math/geometry/Polygon.h
        src/math/geometry/Triangle.cpp
        inc/math/geometry/Triangle.h
        src/objects/Mesh.cpp
        inc/objects/Mesh.h
        inc/static/Config.h
        inc/logging/ExceptionsHandler.h
        src/math/Math.cpp
        inc/math/Math.h
        src/utils/TimeProvider.cpp
        inc/utils/TimeProvider.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Inc)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)
add_dependencies(${PROJECT_NAME} eigen)