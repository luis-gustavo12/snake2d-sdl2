//
// Created by starc on 28/09/2025.
//

#ifndef SNAKE_GAME_SDL2_ENTITY_H
#define SNAKE_GAME_SDL2_ENTITY_H
#include <memory>
#include <SDL_render.h>


class Entity {

public:
	virtual ~Entity() = default;
	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void SetTexture(SDL_Texture* texture) = 0;

protected:
	SDL_Texture* texture = nullptr;


};


#endif //SNAKE_GAME_SDL2_ENTITY_H