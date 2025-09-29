//
// Created by starc on 28/09/2025.
//

#include "core/Engine.h"

#include <iostream>
#include <SDL.h>

#include "entities/AppleEntity.h"
#include "states/GameplayState.h"


int Engine::Init(const char* windowName, int windowWidth, int windowHeight) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize SDL: " <<  SDL_GetError() <<"\n";
		return 0;
	}

	window = SDL_CreateWindow("SDL2 Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	if (!window) {
		std::cout << "Failed to initialize SDL Window: " << SDL_GetError() << "\n";
		return 0;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer) {
		std::cout << "Failed to initialize renderer: " << SDL_GetError() << "\n";
		return 0;
	}

	currentState = std::make_unique<GameplayState>(renderer);

	currentState->OnStateBegin();

	std::cout << "Engine initialized\n";

	return 1;

}

void Engine::Run() {

	SDL_UpdateWindowSurface(window);
	SDL_Event event;

	while (run) {
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

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		currentState->Render(renderer);

		SDL_RenderPresent(renderer);

	}

}

Engine::~Engine() {
	std::cout << "Shutting down engine\n";
	if (window) SDL_DestroyWindow(window);
	if (renderer) SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

