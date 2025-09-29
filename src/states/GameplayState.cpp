//
// Created by starc on 28/09/2025.
//

#include "states/GameplayState.h"

#include <iostream>

#include "entities/AppleEntity.h"

void GameplayState::HandleEvents(const SDL_Event &e) {

	if (e.type == SDL_KEYDOWN) {
		std::cout << "Key pressed: " << e.key.keysym.sym << "\n";
		switch (e.key.keysym.sym) {

			case SDLK_UP:
				std::cout << "Up key pressed!!\n";
				break;
		}
	}

}

void GameplayState::Update() {
}

void GameplayState::Render(SDL_Renderer* renderer) {

	SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
	SDL_RenderClear(renderer);

	for (const auto& entity : entities) {
		entity->Render(renderer);
	}

}

void GameplayState::AddEntity(std::unique_ptr<Entity> entity) {
	this->entities.push_back(std::move(entity));
}

void GameplayState::OnStateBegin() {
	std::unique_ptr<Entity> apple = AppleEntity::Create(ASSET_DIR "/apple.png", renderer);
	if (apple)
		AddEntity(std::move(apple));
}

void GameplayState::OnStateExit() {
	entities.clear();
}
