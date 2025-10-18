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
            SDL_Event quitEv {.type = SDL_QUIT};
            SDL_PushEvent(&quitEv);
            PLOG_DEBUG << "Quitting game!!";
        }
    }
}

void MenuState::Update(float deltaTime){
}

void MenuState::Render(SDL_Renderer* renderer){
    ImGui::Begin("Main Menu");
    ImGui::Text("Snake Game Menu");
    ImGui::Separator();
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
