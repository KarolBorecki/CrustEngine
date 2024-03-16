cmake_minimum_required(VERSION 3.14)
project(CrustEngine)

set(SOURCES
        main.cpp
        src/core/Core.cpp
        src/core/Scene.cpp
        src/core/Window.cpp
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
        src/files/MeshLoader.cpp
)

set(HEADERS
        inc/CrustEngine.h
        inc/core/Core.h
        inc/core/Scene.h
        inc/core/Window.h
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
        inc/files/MeshLoader.h
)

include_directories(${PROJECT_SOURCE_DIR}/inc)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if (${APPLE})
    include(ExternalProject)
    set(SDL_PATH ${CMAKE_BINARY_DIR}/sdl)
    ExternalProject_Add(sdl
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.30.0
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${SDL_PATH}
    )
    include_directories(${SDL_PATH}/include)
    link_directories(${SDL_PATH}/lib)
    target_link_libraries(${PROJECT_NAME} ${SDL_PATH}/lib/libSDL2.dylib)

    set(EIGEN_PATH ${CMAKE_BINARY_DIR}/eigen)
    ExternalProject_Add(eigen
            GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
            GIT_TAG 3.4.0
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EIGEN_PATH}
    )
    include_directories(${EIGEN_PATH}/include/eigen3)

    add_dependencies(${PROJECT_NAME} sdl eigen)

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
endif()

if(WIN32) # check doesnt work
    SET(EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
    SET(CMAKE_MODULE_PATH "$ENV{EIGEN3_DIR}")

    find_package(Eigen3 3.3 REQUIRED)
    include_directories(${EIGEN3_INCLUDE_DIR})

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    target_link_libraries(${PROJECT_NAME}  ${SDL2_LIBRARIES})
endif(WIN32)


set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
