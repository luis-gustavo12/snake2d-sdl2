//
// Created by starc on 30/09/2025.
//

#include "../../headers/entities/SnakeEntity.h"

#include <iostream>

SnakeEntity::~SnakeEntity() {
}

void SnakeEntity::Update(float deltaTime) {

	float distance = deltaTime * speed;

	if (this->direction == EDirection::Down) {
		positionRect.y += distance;
		textureDirection = downTexture;
	}
	else if (this->direction == EDirection::Left) {
		positionRect.x -= distance;
		textureDirection = leftTexture;
	}
	else if (this->direction == EDirection::Right) {
		positionRect.x += distance;
		textureDirection = rightTexture;
	}
	else if (this->direction == EDirection::Up) {
		positionRect.y -= distance;
		textureDirection = upTexture;
	}


}

void SnakeEntity::Render(SDL_Renderer *renderer) {

	SDL_RenderCopy(
		renderer, textureDirection, nullptr, &positionRect
	);

	textureDirection = nullptr;


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

void SnakeEntity::SetTextureDirection(ETextureDirection direction, SDL_Texture* texture){

	switch (direction) {
	case UP:
		upTexture = texture;
		break;
	case DOWN:
		downTexture = texture;
		break;
	case LEFT:
		leftTexture = texture;
		break;
	case RIGHT:
		rightTexture = texture;
		break;
	}

}
