//
// Created by starc on 22/10/2025.
//

#include "../../headers/states/GameOverState.h"

void GameOverState::HandleEvents(const SDL_Event& e){
}

void GameOverState::Update(float deltaTime){
}

void GameOverState::Render(SDL_Renderer* renderer){
    ImGui::Begin("Game Over", nullptr, flags);
    if (ImGui::Button("Start Again")){
        SetNewState(EGameState::Gameplay);
    }
    if (ImGui::Button("Quit")){
        SDL_Event ev {.type = SDL_QUIT};
        SDL_PushEvent(&ev);
    }
    ImGui::End();
}

void GameOverState::AddEntity(std::unique_ptr<Entity> entity){
}

void GameOverState::OnStateBegin(){

}

void GameOverState::OnStateExit(){
}
