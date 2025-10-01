//
// Created by starc on 28/09/2025.
//

#include "entities/AppleEntity.h"

#include <iostream>
#include <SDL_image.h>

#include "core/Texture.h"
#include "entities/EntityFactory.h"

std::unique_ptr<Entity> AppleEntity::Create(const char *imagePath, SDL_Renderer *renderer) {

	SDL_Texture* texture = TextureHandler::CreateTexture(imagePath, renderer);

	if (!texture) {
		std::cout << "Couldn't load texture: "<< SDL_GetError() <<"!!\n";
		return nullptr;
	}

	std::unique_ptr<Entity> apple = EntityFactory::CreateEntity(EGameEntity::Apple, renderer);

	return apple;

}

AppleEntity::~AppleEntity() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void AppleEntity::Update() {

}

void AppleEntity::Render(SDL_Renderer *renderer) {
	SDL_Point center = {positionRect.w / 2, positionRect.h / 2};
	SDL_RenderCopyEx(
		renderer, texture, nullptr, &positionRect, 45.0, &center, SDL_FLIP_NONE
	);
	//SDL_RenderCopy(renderer, texture, nullptr, &positionRect);

}

void AppleEntity::SetTexture(SDL_Texture *texture) {
	this->texture = texture;
}

void AppleEntity::HandleInput(const SDL_Event &e) {

	if (e.type == SDL_KEYDOWN) {

	switch (e.key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w: {
			break;
		}
		default:
			break;
	}

	}

}

void AppleEntity::SetRect(int x, int y, int w, int h) {
	this->positionRect = {x, y, w, h};
}

void AppleEntity::SetPoint(int x, int y) {
	this->point = {x, y};
}