//
// Created by starc on 30/09/2025.
//

#include "../../headers/entities/SnakeEntity.h"

#include <iostream>

#include "core/Texture.h"
#include "plog/Log.h"

SnakeEntity::~SnakeEntity() {
	snakeBody.clear();

	// Heads
	if (upHead) SDL_DestroyTexture(upHead);
	if (downHead) SDL_DestroyTexture(downHead);
	if (leftHead) SDL_DestroyTexture(leftHead);
	if (rightHead) SDL_DestroyTexture(rightHead);

	// Body Corners
	if (bodyBottomLeft) SDL_DestroyTexture(bodyBottomLeft);
	if (bodyBottomRight) SDL_DestroyTexture(bodyBottomRight);
	if (bodyTopLeft) SDL_DestroyTexture(bodyTopLeft);
	if (bodyTopRight) SDL_DestroyTexture(bodyTopRight);

	// Tails
	if (tailDown) SDL_DestroyTexture(tailDown);
	if (tailLeft) SDL_DestroyTexture(tailLeft);
	if (tailRight) SDL_DestroyTexture(tailRight);
	if (tailUp) SDL_DestroyTexture(tailUp);

	// Straight Body Parts
	if (bodyHorizontal) SDL_DestroyTexture(bodyHorizontal);
	if (bodyVertical) SDL_DestroyTexture(bodyVertical);

	upHead = nullptr;
	downHead = nullptr;
	leftHead = nullptr;
	rightHead = nullptr;
	bodyBottomLeft = nullptr;
	bodyBottomRight = nullptr;
	bodyTopLeft = nullptr;
	bodyTopRight = nullptr;
	tailDown = nullptr;
	tailLeft = nullptr;
	tailRight = nullptr;
	tailUp = nullptr;
	bodyHorizontal = nullptr;
	bodyVertical = nullptr;
}

void SnakeEntity::Update(float deltaTime) {

	moveTimer += deltaTime;

	if (moveTimer >= moveInterval){
		moveTimer = 0.0f;

		if (grow){
			SnakeSegment segment = snakeBody.back();
			snakeBody.push_back(segment);
			grow = false;
		}

		for (size_t i = snakeBody.size() - 1; i > 0; i--){
			snakeBody[i].rect = snakeBody[i - 1].rect;
			snakeBody[i].direction = snakeBody[i - 1].direction;
		}

		SnakeSegment& head = snakeBody[0];
		head.direction = nextDirection;
		currentDirection = nextDirection;
		switch (nextDirection){
		case EDirection::Up:
			head.rect.y -= tiles;
			break;
		case EDirection::Down:
			head.rect.y += tiles;
			break;
		case EDirection::Left:
			head.rect.x -= tiles;
			break;
		case EDirection::Right:
			head.rect.x += tiles;
			break;
		}



		if (snakeBody.size() > 3){
			for (size_t i = 3; i < snakeBody.size(); i++){
				if (SDL_HasIntersection(&head.rect, &snakeBody[i].rect)){
					PLOG_INFO << "--- COLLISION DETECTED! ---";
					PLOG_INFO << "Snake Size: " << snakeBody.size();
					PLOG_INFO << "Head's NEXT position: (" << head.rect.x << ", " << head.rect.y << "," << head.rect.w  << ", " << head.rect.h <<")";
					PLOG_INFO << "Body segment [" << i << "] CURRENT position: (" << snakeBody[i].rect.x << ", " << snakeBody[i].rect.y << ", " << head.rect.w << ", " << head.rect.h <<")";
					PLOG_INFO << "Current moving direction: " << static_cast<int>(currentDirection);
					PLOG_INFO << "Next intended direction: " << static_cast<int>(nextDirection);
					PLOG_INFO << "---------------------------";
					gameOver = true;
				}
			}
		}


	}

}

void SnakeEntity::Render(SDL_Renderer *renderer) {

	UpdateTextures();

	for (const auto& segment : snakeBody){
		SDL_RenderCopy(
			renderer, segment.texture, nullptr, &segment.rect
		);
	}




}

void SnakeEntity::HandleInput(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN) {

		switch (e.key.keysym.sym) {
			case SDLK_LEFT:
			case SDLK_a: {
				if (this->currentDirection != EDirection::Right)
					this->nextDirection = EDirection::Left;
				break;
			}
			case SDLK_RIGHT:
			case SDLK_d: {
				if (this->currentDirection != EDirection::Left)
					this->nextDirection = EDirection::Right;
				break;
			}

			case SDLK_UP:
			case SDLK_w: {
				if (this->currentDirection != EDirection::Down)
					this->nextDirection = EDirection::Up;
				break;
			}

			case SDLK_DOWN:
			case SDLK_s: {
				if (this->currentDirection != EDirection::Up)
					this->nextDirection = EDirection::Down;
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

void SnakeEntity::SetDirection(EDirection newDirection) {
	this->currentDirection = newDirection;
}
void SnakeEntity::InitTextures(SDL_Renderer* renderer){

	upHead = TextureHandler::CreateTexture(ASSET_DIR "/head_up.png", renderer);
	downHead = TextureHandler::CreateTexture(ASSET_DIR "/head_down.png", renderer);
	leftHead = TextureHandler::CreateTexture(ASSET_DIR "/head_left.png", renderer);
	rightHead = TextureHandler::CreateTexture(ASSET_DIR "/head_right.png", renderer);

	bodyBottomLeft = TextureHandler::CreateTexture(ASSET_DIR "/body_bottomleft.png", renderer);
	bodyBottomRight = TextureHandler::CreateTexture(ASSET_DIR "/body_bottomright.png", renderer);
	bodyTopLeft = TextureHandler::CreateTexture(ASSET_DIR "/body_topleft.png", renderer);
	bodyTopRight = TextureHandler::CreateTexture(ASSET_DIR "/body_topright.png", renderer);

	tailDown = TextureHandler::CreateTexture(ASSET_DIR "/tail_down.png", renderer);
	tailLeft = TextureHandler::CreateTexture(ASSET_DIR "/tail_left.png", renderer);
	tailRight = TextureHandler::CreateTexture(ASSET_DIR "/tail_right.png", renderer);
	tailUp = TextureHandler::CreateTexture(ASSET_DIR "/tail_up.png", renderer);

	bodyHorizontal = TextureHandler::CreateTexture(ASSET_DIR "/body_horizontal.png", renderer);
	bodyVertical = TextureHandler::CreateTexture(ASSET_DIR "/body_vertical.png", renderer);

	if (!upHead || !downHead || !leftHead || !rightHead ||
		!bodyBottomLeft || !bodyBottomRight || !bodyTopLeft || !bodyTopRight ||
		!tailDown || !tailLeft || !tailRight || !tailUp ||
		!bodyHorizontal || !bodyVertical){
		std::cout << "Failed to initialize textures: " << SDL_GetError() << "\n";
	}

}

void SnakeEntity::InitHead(int x, int y){

	int width, height;

	if (!downHead){
		return;
	}

	SDL_QueryTexture(downHead, nullptr, nullptr, &width, &height);

	SnakeSegment segment = {
		SDL_Rect(x, y, width, height),
		EDirection::Down,
		downHead
	};

	snakeBody.push_back(segment);


}

void SnakeEntity::UpdateTextures(){

	SnakeSegment& head = snakeBody[0];
	switch (currentDirection){
	case EDirection::Up: head.texture = upHead; break;
	case EDirection::Down: head.texture = downHead; break;
	case EDirection::Left: head.texture = leftHead; break;
	case EDirection::Right: head.texture = rightHead; break;
	}

	if (snakeBody.size() <= 1){
		return;
	}

	// Update body, until the tail

	for (size_t i = 1; i < snakeBody.size() - 1; i++){

		SnakeSegment& currentSeg = snakeBody[i];
		SnakeSegment& previousSeg = snakeBody[i - 1];
		// If they're on the same direction
		if (currentSeg.direction == previousSeg.direction){
			// We need to know now if it is horizontal, or vertical
			if (currentSeg.direction == EDirection::Left || currentSeg.direction == EDirection::Right){
				currentSeg.texture = bodyHorizontal;
			} else
				currentSeg.texture = bodyVertical;
		} else{
			// It's a curve, not we need to know where this curves points to
			if (currentSeg.direction == EDirection::Right && previousSeg.direction == EDirection::Down
				|| currentSeg.direction == EDirection::Up && previousSeg.direction == EDirection::Left){
				currentSeg.texture = bodyBottomLeft;
			} else if (currentSeg.direction == EDirection::Right && previousSeg.direction == EDirection::Up ||
				currentSeg.direction == EDirection::Down && previousSeg.direction == EDirection::Left)
				currentSeg.texture = bodyTopLeft;
			else if (currentSeg.direction == EDirection::Left && previousSeg.direction == EDirection::Up
				|| currentSeg.direction == EDirection::Down && previousSeg.direction == EDirection::Right)
				currentSeg.texture = bodyTopRight;
			else if (currentSeg.direction == EDirection::Left && previousSeg.direction == EDirection::Down ||
				currentSeg.direction == EDirection::Up && previousSeg.direction == EDirection::Right)
				currentSeg.texture = bodyBottomRight;

		}

	}

	// Now, the tail
	SnakeSegment& tail = snakeBody.back();
	SnakeSegment& prevTail = snakeBody[snakeBody.size() - 2];
	switch (prevTail.direction){
	case EDirection::Up:
		tail.texture = tailDown;
		break;
	case EDirection::Down:
		tail.texture = tailUp;
		break;
	case EDirection::Left:
		tail.texture = tailRight;
		break;
	case EDirection::Right:
		tail.texture = tailLeft;
		break;
	}



}

std::vector<SDL_Rect> SnakeEntity::GetSnakeSegmentRects(){

	std::vector<SDL_Rect> aux;
	aux.reserve(snakeBody.size());

	for (auto iter: snakeBody){
		aux.push_back(iter.rect);
	}

	return aux;

}

void SnakeEntity::Grow(){
	grow = true;
}

SDL_Rect SnakeEntity::GetSnakeHeadRect(){
	if (!snakeBody.empty()) return snakeBody[0].rect;
	return SDL_Rect{0, 0, 0, 0};
}

size_t SnakeEntity::GetSnakeSize(){
	return snakeBody.size();
}

