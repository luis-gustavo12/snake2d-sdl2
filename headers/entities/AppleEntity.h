//
// Created by starc on 28/09/2025.
//

#ifndef SNAKE_GAME_SDL2_APPLEENTITY_H
#define SNAKE_GAME_SDL2_APPLEENTITY_H
#include "Entity.h"

class AppleEntity : public Entity {
public:
	static std::unique_ptr<Entity> Create(const char *imagePath, SDL_Renderer *renderer);

	~AppleEntity() override;

	void Update() override;

	void Render(SDL_Renderer *renderer) override;

	void SetTexture(SDL_Texture *texture) override;

private:
	AppleEntity() = default;

};



#endif //SNAKE_GAME_SDL2_APPLEENTITY_H