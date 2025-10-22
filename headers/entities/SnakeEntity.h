//
// Created by starc on 30/09/2025.
//

#ifndef SNAKE_GAME_SDL2_SNAKEENTITY_H
#define SNAKE_GAME_SDL2_SNAKEENTITY_H
#include <vector>

#include "entities/Entity.h"

enum class ETextureType {
	HEAD_UP, HEAD_DOWN, HEAD_LEFT, HEAD_RIGHT,
	BODY_UP, BODY_DOWN, BODY_LEFT, BODY_RIGHT,
	TAIL_UP, TAIL_DOWN, TAIL_LEFT, TAIL_RIGHT
};

struct SnakeSegment {
	SDL_Rect rect;
	EDirection direction;
	SDL_Texture* texture;
};

class EntityFactory;

class SnakeEntity : public Entity{
public:
	~SnakeEntity() override;

	void Update(float deltaTime) override;

	void Render(SDL_Renderer *renderer) override;

	void HandleInput(const SDL_Event &e) override;

	void SetTexture(SDL_Texture *texture) override;

	void SetDirection(EDirection newDirection);

	void InitTextures(SDL_Renderer* renderer);

	void InitHead(int x, int y);

	void UpdateTextures();

	std::vector<SDL_Rect> GetSnakeSegmentRects();

	void Grow();
	SDL_Rect GetSnakeHeadRect();

	size_t GetSnakeSize();

	inline bool GameOver() const{return gameOver;}

	void SetTilesSizeByTexture();

private:

	friend EntityFactory;

	SnakeEntity() = default;

	EDirection currentDirection = EDirection::Down;
	EDirection nextDirection = EDirection::Down;

	// Textures for the head
	SDL_Texture* upHead = nullptr;
	SDL_Texture* leftHead = nullptr;
	SDL_Texture* rightHead = nullptr;
	SDL_Texture* downHead = nullptr;

	// Textures for the body, on curves
	SDL_Texture* bodyBottomLeft = nullptr;
	SDL_Texture* bodyBottomRight = nullptr;
	SDL_Texture* bodyTopLeft = nullptr;
	SDL_Texture* bodyTopRight = nullptr;


	SDL_Texture* bodyVertical = nullptr;
	SDL_Texture* bodyHorizontal = nullptr;

	SDL_Texture* tailDown = nullptr;
	SDL_Texture* tailLeft = nullptr;
	SDL_Texture* tailUp = nullptr;
	SDL_Texture* tailRight = nullptr;

	float moveInterval = 0.2;
	float moveTimer = 0.0f;
	float snakeSpeed = 200.0f;
	float angle = Angle::ANGLE_RIGHT;
	int tiles;
	bool grow = false;

	std::vector<SnakeSegment> snakeBody;

	bool gameOver = false;
};


#endif //SNAKE_GAME_SDL2_SNAKEENTITY_H