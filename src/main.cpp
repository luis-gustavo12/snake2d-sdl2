#include <iostream>

#include "../headers/core/Engine.h"
#include "SDL.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

int main(int argc, char* argv[]) {

	plog::init(plog::debug, GAME_LOG_PATH);
	std::cout << ASSET_DIR << "\n";
	PLOG_INFO << "Game started!";

	Engine Engine;

	if (int status = Engine.Init("SDL 2 Snake Game", WINDOW_WIDTH, WINDOW_HEIGHT))
		Engine.Run();
	PLOG_INFO << "Game exited cleanly.";

	return 0;
}