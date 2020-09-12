cmake_minimum_required(VERSION 3.12)

project(roguelike)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(libs)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

add_executable(
    roguelike
    src/main.cpp
    src/window.cpp
    src/application.cpp
    src/game/game.cpp
    src/game/systems/age.cpp
    src/game/systems/camera.cpp
    src/game/systems/fire.cpp
    src/game/systems/health.cpp
    src/game/systems/input.cpp
    src/game/systems/movement.cpp
    src/game/systems/movement_input.cpp
    src/game/systems/render.cpp
    src/game/systems/render_debug.cpp
    src/game/systems/spells.cpp
    src/game/systems/timer.cpp
    src/render/renderer.cpp
    src/render/texture.cpp
)

target_link_libraries(roguelike ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
