//
// Created by starc on 28/09/2025.
//

#include "states/GameplayState.h"

#include <iostream>
#include <SDL_image.h>

#include "core/Texture.h"
#include "entities/AppleEntity.h"
#include "entities/EntityFactory.h"
#include "entities/SnakeEntity.h"

void GameplayState::HandleEvents(const SDL_Event &e) {

	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			SDL_Event quitEvent;
			quitEvent.type = SDL_QUIT;
			SDL_PushEvent(&quitEvent);
			return;
		}
	}

	for (const auto& entity : entities) {
		entity->HandleInput(e);
	}
}

void GameplayState::Update(float deltaTime) {
	for (const auto& entity : entities) {
		entity->Update(deltaTime);
	}

	// Check for collisions
	if (applePtr && snakePtr){
		SDL_Rect appleRect = applePtr->GetRect();
		SDL_Rect snakeRect = snakePtr->GetRect();

		if (SDL_HasIntersection(&appleRect, &snakeRect)){
			std::cout << "intersection\n";
		}

	}



}

void GameplayState::Render(SDL_Renderer* renderer) {

	if (backgroundTexture)
		SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
	else {
		SDL_SetRenderDrawColor(renderer, 144, 238, 144, 255);
		SDL_RenderClear(renderer);
	}

	for (const auto& entity : entities) {
		entity->Render(renderer);
	}

}

void GameplayState::AddEntity(std::unique_ptr<Entity> entity) {
	this->entities.push_back(std::move(entity));
}

void GameplayState::OnStateBegin() {

	// Initialize the background
	SDL_Surface* backgroundSurface = IMG_Load(ASSET_DIR "/grass-background.png");
	if (backgroundSurface) {
		this->backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
		SDL_FreeSurface(backgroundSurface);
	} else
		std::cout << "Error:" << SDL_GetError() << "\n";

	if (!renderer) {
		std::cout << "Failed to initialize background texture: " << SDL_GetError() << "\n";
	}

	std::unique_ptr<Entity> apple = EntityFactory::CreateEntity(EGameEntity::Apple, renderer);
	applePtr = dynamic_cast<AppleEntity*>(apple.get());
	if (apple){
		AddEntity(std::move(apple));
	}

	std::unique_ptr<Entity> snakeHead = EntityFactory::CreateEntity(EGameEntity::SnakeHead, renderer);
	snakePtr = dynamic_cast<SnakeEntity*>(snakeHead.get());
	if (snakeHead)
		AddEntity(std::move(snakeHead));

}

void GameplayState::OnStateExit() {
	entities.clear();
	applePtr = nullptr;
	snakePtr = nullptr;
}
