cmake_minimum_required(VERSION 3.14)
project(CrustEngine)

include(ExternalProject)

if (${APPLE})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
endif()

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

set(EIGEN_PATH ${CMAKE_BINARY_DIR}/eigen)
ExternalProject_Add(eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EIGEN_PATH}
)
include_directories(${EIGEN_PATH}/include/eigen3)
link_directories(${EIGEN_PATH}/shared)

set(SOURCES
        main.cpp
        src/core/Core.cpp
        src/core/Scene.cpp
        src/core/Window.cpp
        src/files/MeshLoader.cpp
        src/logging/ExceptionsHandler.cpp
        src/logging/Logger.cpp
        src/math/Math.cpp
        src/math/geometry/Polygon.cpp
        src/math/geometry/Triangle.cpp
        src/objects/Transform.cpp
        src/objects/Object.cpp
        src/objects/Camera.cpp
        src/objects/LightSource.cpp
        src/objects/Mesh.cpp
        src/objects/RenderObject.cpp
        src/rendering/projection/PerspectiveProjector.cpp
        src/rendering/Library2DWrapper.cpp
        src/rendering/Renderer.cpp
        src/utils/TimeProvider.cpp
)

set(HEADERS
        inc/CrustEngine.h
        inc/core/Core.h
        inc/core/Scene.h
        inc/core/Window.h
        inc/files/MeshLoader.h
        inc/logging/Logger.h
        inc/logging/ExceptionsHandler.h
        inc/math/Math.h
        inc/math/Matrix.h
        inc/math/Vector3.h
        inc/math/Vector4.h
        inc/math/geometry/Polygon.h
        inc/math/geometry/Triangle.h
        inc/objects/Transform.h
        inc/objects/Object.h
        inc/objects/Camera.h
        inc/objects/LightSource.h
        inc/objects/Mesh.h
        inc/objects/RenderObject.h
        inc/rendering/projection/AbstractProjector.h
        inc/rendering/projection/PerspectiveProjector.h
        inc/rendering/Library2DWrapper.h
        inc/rendering/Renderer.h
        inc/utils/TimeProvider.h
        inc/scripting/Script.h
        inc/static/Config.h
        inc/static/Definitions.h
        inc/rendering/projection/AbstractProjector.h
)

include_directories(${PROJECT_SOURCE_DIR}/inc)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)
add_dependencies(${PROJECT_NAME} eigen)