cmake_minimum_required(VERSION 4.0)
project(snake_game_sdl2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ASSET_DIR "${CMAKE_SOURCE_DIR}/assets/snake-assets")
set(ASSET_FONTS_DIR "${CMAKE_SOURCE_DIR}/assets/fonts")
set (ASSET_SOUNDS_DIR "${CMAKE_SOURCE_DIR}/assets/sounds")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
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
        src/entities/AppleEntity.cpp
        src/states/StateFactory.cpp
        headers/states/StateFactory.h
        src/entities/EntityFactory.cpp
        headers/entities/EntityFactory.h
        src/entities/SnakeEntity.cpp
        headers/entities/SnakeEntity.h
        src/core/Score.cpp
        headers/entities/Score.h
        src/core/TextManager.cpp
        headers/core/TextManager.h
        src/core/SoundManager.cpp
        headers/core/SoundManager.h)

if (WIN32)
    target_link_libraries(snake_game_sdl2 PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer SDL2::SDL2main)
else()
    target_link_libraries(snake_game_sdl2 PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer)
endif()

target_include_directories(snake_game_sdl2 PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        "${CMAKE_SOURCE_DIR}/headers"
)

target_compile_definitions(snake_game_sdl2 PRIVATE
        ASSET_DIR="${ASSET_DIR}"
        ASSET_FONTS_DIR="${ASSET_FONTS_DIR}"
        ASSET_SOUNDS_DIR="${ASSET_SOUNDS_DIR}"
)

if(WIN32)
    add_custom_command(TARGET snake_game_sdl2 POST_BUILD
            COMMAND_EXPAND_LISTS # <-- This is the fix!
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:snake_game_sdl2>
            $<TARGET_FILE_DIR:snake_game_sdl2>
            COMMENT "Copying runtime DLLs"
    )
endif()