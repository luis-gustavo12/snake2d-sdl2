//
// Created by starc on 28/09/2025.
//

#include "core/Engine.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "plog/Log.h"
#include "states/GameplayState.h"
#include "states/StateFactory.h"


int Engine::Init(const char* windowName, int windowWidth, int windowHeight) {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		PLOG_DEBUG << "Failed to initialize SDL: " <<  SDL_GetError();
		return 0;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		PLOG_DEBUG << "Could not initialize SDL_mixer: " << Mix_GetError();
		return 1;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		PLOG_DEBUG << "Failed to initialize SDL_image: " << IMG_GetError();
		return 0;
	}

	window = SDL_CreateWindow("SDL2 Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	if (!window) {
		PLOG_DEBUG << "Failed to initialize SDL Window: " << SDL_GetError();
		return 0;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		PLOG_DEBUG << "Failed to initialize renderer: " << SDL_GetError();
		return 0;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void) io;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	gameStates.reserve(15);

	auto state = StateFactory::CreateState(EGameState::Gameplay, renderer);

	state->OnStateBegin();

	gameStates.push_back(std::move(state));

	PLOG_DEBUG << "Engine initialized";

	return 1;

}

void Engine::Run() {

	SDL_Event event;
	Uint64 lastTime = SDL_GetPerformanceCounter();
	float deltaTime = 0.0f;
	const float fps = 60.0f;
	const float targetFps = 1.0f / fps;

	while (run) {

		// deltaTime handling
		Uint64 currentTime = SDL_GetPerformanceCounter();
		deltaTime = (float) (currentTime - lastTime) / (float) SDL_GetPerformanceFrequency();
		lastTime = currentTime;

		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			switch (event.type) {
				case SDL_QUIT:
					run = false;
					break;
				default:
					break;
			}
			gameStates.back()->HandleEvents(event);
		}

		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		gameStates.back()->Update(deltaTime);

		for (auto& state : gameStates){
			state->Render(renderer);
		}

		if (gameStates.back()->GetNextState() != EGameState::None){
			switch (gameStates.back()->GetNextState()){
			case EGameState::Gameplay:
				break;
			case EGameState::Menu:{
				PLOG_DEBUG << "Menu";
				auto menu = StateFactory::CreateState(EGameState::Menu, renderer);
				gameStates.push_back(std::move(menu));
			}
				break;
			case EGameState::GameOver:{
				SDL_Event e;
				e.type = SDL_QUIT;
				SDL_PushEvent(&e);
			}
				break;
			default:
				;
			}

		}

		ImGui::Render();
		//ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

		SDL_RenderPresent(renderer);

		Uint64 endTime = SDL_GetPerformanceCounter();
		float elapsedSeconds = (float) (endTime - currentTime) / (float) SDL_GetPerformanceFrequency();

		if (elapsedSeconds < targetFps) {
			SDL_Delay(((targetFps - elapsedSeconds) * 1000.0f));
		}



	}

}

Engine::~Engine() {
	PLOG_DEBUG << "Shutting down engine";

	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (window) SDL_DestroyWindow(window);
	if (renderer) SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
}

