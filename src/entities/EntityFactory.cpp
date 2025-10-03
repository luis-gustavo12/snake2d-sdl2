//
// Created by starc on 30/09/2025.
//

#include "../../headers/entities/EntityFactory.h"

#include <iostream>
#include <SDL_image.h>

#include "../../headers/entities/SnakeEntity.h"
#include "../../headers/entities/AppleEntity.h"
#include "core/Texture.h"

#define TEXTURE_INIT_ERROR std::cout << "Failed to initialize texture: " << IMG_GetError() << "\n"

int width = 50, height = 50;

std::unique_ptr<Entity> EntityFactory::CreateEntity(EGameEntity entityNumber, SDL_Renderer* renderer) {

	switch (entityNumber) {
		case EGameEntity::Apple: {

			SDL_Texture* texture = TextureHandler::CreateTexture(ASSET_DIR "/apple.png", renderer);

			if (!texture) {
				TEXTURE_INIT_ERROR;
				return nullptr;
			}

			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

			//std::unique_ptr<Entity> apple (new AppleEntity());
			auto apple = std::unique_ptr<Entity>(new AppleEntity());
			//auto apple = std::make_unique<AppleEntity>();
			apple->SetTexture(texture);

			int screenCenterX = 800 / 2;
			int screenCenterY = 600 / 2;

			// Calculate top-left corner to center the texture
			int x = screenCenterX - (width / 2);
			int y = screenCenterY - (height / 2);

			apple->SetRect(x, y, width, height);
			apple->SetPoint(width / 2, height / 2);

			return apple;
		}
		case EGameEntity::SnakeHead: {

			SDL_Texture* texture = TextureHandler::CreateTexture(ASSET_DIR "/snake-head.png", renderer);

			if (!texture) {
				TEXTURE_INIT_ERROR;
				return nullptr;
			}

			auto snakeHead = std::unique_ptr<SnakeEntity> (new SnakeEntity());

			snakeHead->SetTexture(texture);

			snakeHead->SetRect(20, 20, width, height);

			snakeHead->SetDirection(EDirection::Right);

			return snakeHead;
		}
		default:
			return nullptr;
	}

}
