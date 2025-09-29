cmake_minimum_required(VERSION 4.0)
project(snake_game_sdl2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ASSET_DIR "${CMAKE_SOURCE_DIR}/assets/snake-assets")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
add_executable(snake_game_sdl2 src/main.cpp
        src/core/Engine.cpp
        headers/core/Engine.h
        src/states/GameState.cpp
        headers/states/GameState.h
        src/states/GameplayState.cpp
        headers/states/GameplayState.h
        src/core/Texture.cpp
        headers/core/Texture.h
        headers/entities/Entity.h
        headers/entities/AppleEntity.h
        src/entities/AppleEntity.cpp)

target_link_libraries(snake_game_sdl2 PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)

target_include_directories(snake_game_sdl2 PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        "${CMAKE_SOURCE_DIR}/headers"
)

target_compile_definitions(snake_game_sdl2 PRIVATE
        ASSET_DIR="${ASSET_DIR}"
)