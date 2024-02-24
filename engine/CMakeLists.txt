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

set(SOURCES Src/main.cpp
        Inc/Rendering/Renderer.hpp
        Inc/Rendering/RendererWrapper.hpp
        Inc/Rendering/RenderWindow.hpp
        Inc/Rendering/Projector.hpp
        Inc/Rendering/Polygon.hpp
        Inc/Rendering/Mesh.hpp
        Inc/Objects/Transform.hpp
        Inc/Objects/RenderObject.hpp
        Inc/Objects/Object.hpp
        Inc/Objects/Camera.hpp
        Inc/Objects/Lightining/LightSource.hpp
        Inc/Objects/Lightining/DirectionalLight.hpp
        Inc/Scripting/CrustScript.hpp
        Inc/Utils/TimeProvider.hpp
        Inc/Math/Math.hpp
        Inc/Math/Matrix.hpp
        Inc/Math/Triangle.hpp
        Inc/Math/Vector3.hpp
        Inc/Math/Vector4.hpp
        Inc/Logging/ExceptionsHandler.hpp
        Inc/Logging/Logger.hpp
        Inc/Logging/ObjectLogger.hpp
        Inc/Input/InputEvent.hpp
        Inc/Input/InputHandler.hpp
        Inc/Files/MeshLoader.hpp
        Inc/Core/Core.hpp
        Inc/Core/Scene.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Inc)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)
add_dependencies(${PROJECT_NAME} eigen)