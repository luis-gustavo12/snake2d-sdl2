//
// Created by starc on 28/09/2025.
//

#ifndef SNAKE_GAME_SDL2_TEXTURE_H
#define SNAKE_GAME_SDL2_TEXTURE_H
#include <SDL_render.h>

class TextureHandler {
public:
	static SDL_Texture* CreateTexture(const char* imagePath, SDL_Renderer* renderer);
};

#endif //SNAKE_GAME_SDL2_TEXTURE_H