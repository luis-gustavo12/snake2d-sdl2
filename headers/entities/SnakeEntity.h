//
// Created by starc on 30/09/2025.
//

#ifndef SNAKE_GAME_SDL2_SNAKEENTITY_H
#define SNAKE_GAME_SDL2_SNAKEENTITY_H
#include <vector>

#include "entities/Entity.h"

#define TILES_MOVE 2

enum class ETextureType {
	HEAD_UP, HEAD_DOWN, HEAD_LEFT, HEAD_RIGHT,
	BODY_UP, BODY_DOWN, BODY_LEFT, BODY_RIGHT,
	TAIL_UP, TAIL_DOWN, TAIL_LEFT, TAIL_RIGHT
};

struct SnakeSegment {
	SDL_Rect rect;
	EDirection direction;
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

	void SetTextureDirection(EDirection direction, SDL_Texture* texture);

	void AddSegment(EDirection direction, SDL_Rect rect);
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

	std::vector<SnakeSegment> snakeBody;
};


#endif //SNAKE_GAME_SDL2_SNAKEENTITY_H