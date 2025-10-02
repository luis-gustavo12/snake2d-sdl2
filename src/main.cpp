#include <iostream>

#include "../headers/core/Engine.h"
#include "SDL.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

int main(int argc, char* argv[]) {

	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;

	std::cout << ASSET_DIR << "\n";

	Engine Engine;

	if (int status = Engine.Init("SDL 2 Snake Game", WINDOW_WIDTH, WINDOW_HEIGHT))
		Engine.Run();


	return 0;
}