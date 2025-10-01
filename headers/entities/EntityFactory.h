//
// Created by starc on 30/09/2025.
//

#ifndef SNAKE_GAME_SDL2_ENTITYFACTORY_H
#define SNAKE_GAME_SDL2_ENTITYFACTORY_H
#include <memory>

#include "Entity.h"

enum class EGameEntity {
	Apple,
	SnakeHead
};

class EntityFactory {
public:
	static std::unique_ptr<Entity> CreateEntity (EGameEntity entityNumber, SDL_Renderer* renderer);

};


#endif //SNAKE_GAME_SDL2_ENTITYFACTORY_H