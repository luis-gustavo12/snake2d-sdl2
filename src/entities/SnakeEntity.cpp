//
// Created by starc on 30/09/2025.
//

#include "../../headers/entities/SnakeEntity.h"

#include <iostream>

SnakeEntity::~SnakeEntity() {
}

void SnakeEntity::Update(float deltaTime) {

	moveTimer += deltaTime;

	if (moveTimer <= moveInterval) return;

	moveTimer -= moveInterval;

	if (this->direction == EDirection::Down) {
		positionRect.y += TILES_MOVE;
		angle = Angle::ANGLE_DOWN;
	}
	else if (this->direction == EDirection::Left) {
		positionRect.x -= TILES_MOVE;
		angle = Angle::ANGLE_LEFT;
	}
	else if (this->direction == EDirection::Right) {
		positionRect.x += TILES_MOVE;
		angle = Angle::ANGLE_RIGHT;
	}
	else if (this->direction == EDirection::Up) {
		positionRect.y -= TILES_MOVE;
		angle = Angle::ANGLE_UP;
	}
}

void SnakeEntity::Render(SDL_Renderer *renderer) {
	//SDL_Point center = {positionRect.w / 2, positionRect.h / 2};
	std::cout << "Direction : " << this->direction << " x: " << positionRect.x << " y: " << positionRect.y << " point.x " << point.x << " point. y: " << point.y << " angle : " << angle << "\n";
	SDL_Point center = {positionRect.w / 2, positionRect.h / 2};
	SDL_RenderCopyEx(
		renderer, texture, nullptr, &positionRect, angle, &center, SDL_FLIP_NONE)
	;


}

void SnakeEntity::HandleInput(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN) {

		switch (e.key.keysym.sym) {
			//
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
