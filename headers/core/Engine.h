//
// Created by starc on 28/09/2025.
//

#ifndef SNAKE_GAME_SDL2_ENGINE_H
#define SNAKE_GAME_SDL2_ENGINE_H
#include <memory>
#include <SDL_video.h>

#include "../states/GameState.h"


class Engine {

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool run = true;

public:
	int Init(const char* windowName, int windowWidth, int windowHeight);
	void Run();
	~Engine();
	std::unique_ptr<GameState> currentState = nullptr;

};


#endif //SNAKE_GAME_SDL2_ENGINE_H