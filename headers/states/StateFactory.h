//
// Created by starc on 30/09/2025.
//

#ifndef SNAKE_GAME_SDL2_STATEFACTORY_H
#define SNAKE_GAME_SDL2_STATEFACTORY_H
#include <memory>

#include "GameState.h"


class StateFactory {

public:
	static std::unique_ptr<GameState> CreateState(EGameState state, SDL_Renderer* renderer);



};


#endif //SNAKE_GAME_SDL2_STATEFACTORY_H