//
// Created by starc on 30/09/2025.
//

#include "../../headers/entities/SnakeEntity.h"

SnakeEntity::~SnakeEntity() {
}

void SnakeEntity::Update(float deltaTime) {

	moveTimer += deltaTime;

	if (moveTimer <= moveInterval) return;

	moveTimer -= moveInterval;

	if (this->direction == EDirection::Down)
		positionRect.y += 32;
	else if (this->direction == EDirection::Left)
		positionRect.x -= 32;
	else if (this->direction == EDirection::Right)
		positionRect.x += 32;
	else if (this->direction == EDirection::Up)
		positionRect.y -= 32;
}

void SnakeEntity::Render(SDL_Renderer *renderer) {
	SDL_Point center = {positionRect.x / 2, positionRect.h / 2};
	SDL_RenderCopyEx(
		renderer, texture, nullptr, &positionRect, 0.0, &center, SDL_FLIP_NONE);

}

void SnakeEntity::HandleInput(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN) {

		switch (e.key.keysym.sym) {

			case SDLK_LEFT:
			case SDLK_a: {
				this->direction = EDirection::Left;
				break;
			}
			case SDLK_RIGHT:
			case SDLK_d: {
				this->direction = EDirection::Right;
				break;
			}

			case SDLK_UP:
			case SDLK_w: {
				this->direction = EDirection::Up;
				break;
			}

			case SDLK_DOWN:
			case SDLK_s: {
				this->direction = EDirection::Down;
				break;
			}

			default:
				break;

		}

	}
}

void SnakeEntity::SetTexture(SDL_Texture *texture) {
	this->texture = texture;
}

void SnakeEntity::SetRect(int x, int y, int w, int h) {
	Entity::SetRect(x, y, w, h);
}

void SnakeEntity::SetPoint(int x, int y) {
	Entity::SetPoint(x, y);
}

void SnakeEntity::SetDirection(EDirection newDirection) {
	this->direction = newDirection;
}
