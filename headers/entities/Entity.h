//
// Created by starc on 28/09/2025.
//

#ifndef SNAKE_GAME_SDL2_ENTITY_H
#define SNAKE_GAME_SDL2_ENTITY_H
#include <memory>
#include <SDL_events.h>
#include <SDL_render.h>


class Entity {

public:
	virtual ~Entity() = default;
	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void HandleInput(const SDL_Event& e) = 0;
	virtual void SetTexture(SDL_Texture* texture) = 0;
	virtual void SetRect(int x, int y, int w, int h) {positionRect = {x, y, w, h};}
	virtual void SetPoint(int x, int y) {point = {x, y};}
protected:
	SDL_Texture* texture = nullptr;
	SDL_Rect positionRect = {};
	SDL_Point point = {};
};


#endif //SNAKE_GAME_SDL2_ENTITY_H