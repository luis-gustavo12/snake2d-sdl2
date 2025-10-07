//
// Created by starc on 28/09/2025.
//

#ifndef SNAKE_GAME_SDL2_GAMESTATE_H
#define SNAKE_GAME_SDL2_GAMESTATE_H
#include <memory>
#include <SDL_events.h>
#include <SDL_render.h>

#include "core/SoundManager.h"
#include "entities/Entity.h"

class Engine;

enum class EGameState{
	Gameplay,
	Menu,
};


class GameState {
public:
	virtual ~GameState() = default;
	virtual void HandleEvents(const SDL_Event& e) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void AddEntity(std::unique_ptr<Entity> entity) = 0;
	virtual void OnStateBegin() = 0;
	virtual void OnStateExit() = 0;

protected:
	SDL_Texture* backgroundTexture = nullptr;
	std::unique_ptr <SoundManager> soundManager = nullptr;

};


#endif //SNAKE_GAME_SDL2_GAMESTATE_H