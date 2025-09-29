//
// Created by starc on 28/09/2025.
//

#include "entities/AppleEntity.h"

#include <iostream>
#include <SDL_image.h>

#include "core/Texture.h"

std::unique_ptr<Entity> AppleEntity::Create(const char *imagePath, SDL_Renderer *renderer) {

	SDL_Texture* texture = TextureHandler::CreateTexture(imagePath, renderer);

	if (!texture) {
		std::cout << "Couldn't load texture: "<< SDL_GetError() <<"!!\n";
		return nullptr;
	}

	std::unique_ptr<Entity> apple (new AppleEntity());
	apple->SetTexture(texture);

	return apple;

}

AppleEntity::~AppleEntity() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void AppleEntity::Update() {
}

void AppleEntity::Render(SDL_Renderer *renderer) {
	SDL_Rect rect = {50, 50, 50, 50};
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void AppleEntity::SetTexture(SDL_Texture *texture) {
	this->texture = texture;
}

