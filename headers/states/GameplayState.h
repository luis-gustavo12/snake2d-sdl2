//
// Created by starc on 28/09/2025.
//

#ifndef SNAKE_GAME_SDL2_GAMEPLAYSTATE_H
#define SNAKE_GAME_SDL2_GAMEPLAYSTATE_H
#include <memory>
#include <vector>

#include "GameState.h"
#include "entities/AppleEntity.h"
#include "entities/Entity.h"
#include "entities/SnakeEntity.h"


class GameplayState : public GameState {

public:

	explicit GameplayState(SDL_Renderer* renderer) : renderer(renderer) {}

	void HandleEvents(const SDL_Event &e) override;

	void Update(float deltaTime) override;

	void Render(SDL_Renderer *renderer) override;

	void AddEntity(std::unique_ptr<Entity> entity) override;

	void OnStateBegin() override;

	void OnStateExit() override;

private:
	SDL_Renderer* renderer;
	std::vector<std::unique_ptr<Entity>> entities;

	AppleEntity* applePtr;
	SnakeEntity* snakePtr;

};


#endif //SNAKE_GAME_SDL2_GAMEPLAYSTATE_H