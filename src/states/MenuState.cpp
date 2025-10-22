//
// Created by starc on 17/10/2025.
//

#include "states/MenuState.h"

#include "imgui.h"
#include "plog/Log.h"

MenuState::~MenuState(){
}

void MenuState::HandleEvents(const SDL_Event& e){
    if (e.type == SDL_KEYDOWN){
        if (e.key.keysym.sym == SDLK_ESCAPE){
            SetNewState(EGameState::GameplayContinue);
        }
    }
}

void MenuState::Update(float deltaTime){
}

void MenuState::Render(SDL_Renderer* renderer){

    ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Always);

    ImGui::Begin("Main Menu", nullptr, flags);
    ImGui::Text("Snake Game Menu");
    ImGui::Separator();
    if (ImGui::Button("Continue")){
        SetNewState(EGameState::GameplayContinue);
    }
    else if (ImGui::Button("Quit")){
        SDL_Event quitEvent {.type = SDL_QUIT};
        SDL_PushEvent(&quitEvent);
    }

    ImGui::Text("Text Wrapped");

    ImGui::End();
}

void MenuState::AddEntity(std::unique_ptr<Entity> entity){
}

void MenuState::OnStateBegin(){
}

void MenuState::OnStateExit(){
}

void MenuState::SetNewState(EGameState newState){
    GameState::SetNewState(newState);
}

EGameState MenuState::GetNextState(){
    return GameState::GetNextState();
}
