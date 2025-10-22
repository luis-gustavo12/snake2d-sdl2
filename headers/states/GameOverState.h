//
// Created by starc on 22/10/2025.
//

#ifndef SNAKE_GAME_SDL2_GAMEOVERSTATE_H
#define SNAKE_GAME_SDL2_GAMEOVERSTATE_H
#include "imgui.h"
#include "states/GameState.h"


class GameOverState : public  GameState{
public:
    explicit GameOverState() {}
    void HandleEvents(const SDL_Event& e) override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;
    void AddEntity(std::unique_ptr<Entity> entity) override;
    void OnStateBegin() override;
    void OnStateExit() override;

private:
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

};


#endif //SNAKE_GAME_SDL2_GAMEOVERSTATE_H