//
// Created by starc on 28/09/2025.
//

#ifndef SNAKE_GAME_SDL2_ENTITY_H
#define SNAKE_GAME_SDL2_ENTITY_H
#include <memory>
#include <SDL_events.h>
#include <SDL_render.h>


struct Angle {
	static constexpr double ANGLE_UP = 270.0;
	static constexpr double ANGLE_LEFT = 180.0;
	static constexpr double ANGLE_DOWN = 90.0;
	static constexpr double ANGLE_RIGHT = 0.0;
};


enum class EDirection {
	Up, Down, Left, Right
};

inline std::ostream& operator<<(std::ostream& os, const EDirection& dir) {
	switch (dir) {
		case EDirection::Up:
			os << "Up";
			break;
		case EDirection::Down:
			os << "Down";
			break;
		case EDirection::Left:
			os << "Left";
			break;
		case EDirection::Right:
			os << "Right";
			break;
	}
	return os;
}



class Entity {

public:
	virtual ~Entity() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void HandleInput(const SDL_Event& e) = 0;
	virtual void SetTexture(SDL_Texture* texture) = 0;
	virtual void SetRect(int x, int y, int w, int h) {positionRect = {x, y, w, h};}
	virtual void SetPoint(int x, int y) {point = {x, y};}
protected:
	SDL_Texture* texture = nullptr;
	SDL_Rect positionRect = {};
	SDL_Point point = {};
};


#endif //SNAKE_GAME_SDL2_ENTITY_H