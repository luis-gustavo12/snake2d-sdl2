//
// Created by starc on 28/09/2025.
//

#include "core/Texture.h"

#include <iostream>
#include <SDL2/SDL_image.h>

SDL_Texture* TextureHandler::CreateTexture(const char *imagePath, SDL_Renderer *renderer) {

	SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath);

	if (!texture) std::cout << "Failed to initialize texture!!\n";

	return texture;

}
