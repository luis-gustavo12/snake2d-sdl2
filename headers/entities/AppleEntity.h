//
// Created by starc on 28/09/2025.
//

#ifndef SNAKE_GAME_SDL2_APPLEENTITY_H
#define SNAKE_GAME_SDL2_APPLEENTITY_H
#include "Entity.h"

class EntityFactory;

class AppleEntity : public Entity {
public:
	static std::unique_ptr<Entity> Create(const char *imagePath, SDL_Renderer *renderer);

	~AppleEntity() override;

	void Update(float deltaTime) override;

	void Render(SDL_Renderer *renderer) override;

	void SetTexture(SDL_Texture *texture) override;

	void HandleInput(const SDL_Event &e) override;

	void SetRect(int x, int y, int w, int h) override;

	void SetPoint(int x, int y) override;

private:
	friend class EntityFactory;

	AppleEntity() = default;

};



#endif //SNAKE_GAME_SDL2_APPLEENTITY_H