//
// Created by starc on 28/09/2025.
//

#include "core/Engine.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "states/GameplayState.h"
#include "states/StateFactory.h"


int Engine::Init(const char* windowName, int windowWidth, int windowHeight) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize SDL: " <<  SDL_GetError() <<"\n";
		return 0;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "Failed to initialize SDL_image: " << IMG_GetError() << "\n";
		return 0;
	}

	window = SDL_CreateWindow("SDL2 Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	if (!window) {
		std::cout << "Failed to initialize SDL Window: " << SDL_GetError() << "\n";
		return 0;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "Failed to initialize renderer: " << SDL_GetError() << "\n";
		return 0;
	}

	currentState = StateFactory::CreateState(EGameState::Gameplay, renderer);

	currentState->OnStateBegin();

	std::cout << "Engine initialized\n";

	return 1;

}

void Engine::Run() {

	SDL_Event event;
	Uint64 lastTime = SDL_GetPerformanceCounter();
	float deltaTime = 0.0f;

	while (run) {

		// deltaTime handling
		Uint64 currentTime = SDL_GetPerformanceCounter();
		deltaTime = (float) (currentTime - lastTime) / (float) SDL_GetPerformanceFrequency();
		lastTime = currentTime;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					run = false;
					break;
				default:
					break;
			}
			currentState->HandleEvents(event);
		}

		currentState->Update(deltaTime);

		currentState->Render(renderer);

		SDL_RenderPresent(renderer);


	}

}

Engine::~Engine() {
	std::cout << "Shutting down engine\n";
	if (window) SDL_DestroyWindow(window);
	if (renderer) SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
}

