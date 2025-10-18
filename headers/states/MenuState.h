//
// Created by starc on 17/10/2025.
//

#ifndef SNAKE_GAME_SDL2_MENUSTATE_H
#define SNAKE_GAME_SDL2_MENUSTATE_H
#include "GameState.h"


class MenuState : public GameState{
public:
    explicit MenuState(SDL_Renderer* renderer) : renderer(renderer) {}
    ~MenuState() override;
    void HandleEvents(const SDL_Event& e) override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;
    void AddEntity(std::unique_ptr<Entity> entity) override;
    void OnStateBegin() override;
    void OnStateExit() override;
    void SetNewState(EGameState newState) override;
    EGameState GetNextState() override;

private:
    SDL_Renderer* renderer;
};


#endif //SNAKE_GAME_SDL2_MENUSTATE_H