//
// Created by starc on 28/09/2025.
//

#include "entities/AppleEntity.h"

#include <chrono>
#include <iostream>
#include <random>
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

	SDL_Window* window = SDL_RenderGetWindow(renderer);

	return apple;

}

AppleEntity::~AppleEntity() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void AppleEntity::Update(float deltaTime) {

}

void AppleEntity::Render(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, texture, nullptr, &positionRect);
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

	void AppleEntity::Respawn(SDL_Renderer* renderer){
		int w, h;
		SDL_Window* window = SDL_RenderGetWindow(renderer);
		if (window){
			SDL_GetWindowSize(window, &w, &h);
			unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

			int maxX = w - positionRect.w;
			int maxY = h - positionRect.h;

			std::default_random_engine generator(seed);
			std::uniform_int_distribution<int> distX (0, maxX);
			std::uniform_int_distribution<int> distY (0, maxY);

			SetRect(distX(generator), distY(generator), positionRect.w, positionRect.h);


		}
	}
