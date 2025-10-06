//
// Created by starc on 30/09/2025.
//

#ifndef SNAKE_GAME_SDL2_SNAKEENTITY_H
#define SNAKE_GAME_SDL2_SNAKEENTITY_H
#include "entities/Entity.h"

#define TILES_MOVE 2

enum ETextureDirection {
	UP, DOWN, LEFT, RIGHT
};

class EntityFactory;

class SnakeEntity : public Entity{
public:
	~SnakeEntity() override;

	void Update(float deltaTime) override;

	void Render(SDL_Renderer *renderer) override;

	void HandleInput(const SDL_Event &e) override;

	void SetTexture(SDL_Texture *texture) override;

	void SetRect(int x, int y, int w, int h) override;

	void SetPoint(int x, int y) override;

	void SetDirection(EDirection newDirection);

	void SetTextureDirection(ETextureDirection direction, SDL_Texture* texture);
private:

	friend EntityFactory;

	SnakeEntity() = default;

	EDirection direction = EDirection::Down;

	SDL_Texture* upTexture = nullptr;
	SDL_Texture* downTexture = nullptr;
	SDL_Texture* leftTexture = nullptr;
	SDL_Texture* rightTexture = nullptr;

	SDL_Texture* textureDirection = nullptr;

	float moveInterval = 0.2;
	float moveTimer = 0.0f;
	float speed = 200.0f;
	float angle = Angle::ANGLE_RIGHT;
};


#endif //SNAKE_GAME_SDL2_SNAKEENTITY_H