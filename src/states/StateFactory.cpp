//
// Created by starc on 30/09/2025.
//

#include "../../headers/states/StateFactory.h"

#include "../../headers/states/GameplayState.h"
#include "states/MenuState.h"

std::unique_ptr<GameState> StateFactory::CreateState(EGameState state, SDL_Renderer *renderer) {

	switch (state) {
		case EGameState::Gameplay: {
			return std::make_unique<GameplayState>(renderer);
		}
		case EGameState::Menu:{
			return std::make_unique<MenuState>(renderer);
		}
		default:
			return nullptr;
	}

}
