//
// Created by starc on 30/09/2025.
//

#ifndef SNAKE_GAME_SDL2_SNAKEENTITY_H
#define SNAKE_GAME_SDL2_SNAKEENTITY_H
#include "entities/Entity.h"

class EntityFactory;

class SnakeEntity : public Entity{
public:
	~SnakeEntity() override;

	void Update() override;

	void Render(SDL_Renderer *renderer) override;

	void HandleInput(const SDL_Event &e) override;

	void SetTexture(SDL_Texture *texture) override;

	void SetRect(int x, int y, int w, int h) override;

	void SetPoint(int x, int y) override;

	void SetDirection(EDirection newDirection);
private:

	friend EntityFactory;

	SnakeEntity() = default;

	EDirection direction;

};


#endif //SNAKE_GAME_SDL2_SNAKEENTITY_H