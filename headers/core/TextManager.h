//
// Created by luisg on 06/10/2025.
//

#ifndef SNAKE_GAME_SDL2_TEXTMANAGER_H
#define SNAKE_GAME_SDL2_TEXTMANAGER_H
#include <memory>
#include <iostream>
#include <SDL_ttf.h>

#define TTF_ERROR_MSG std::cout << "TTF Error: " << TTF_GetError() << "\n";

class TextManager {
public:
    TextManager() = default;
    static std::unique_ptr<TextManager> Create(const char* filePath, int fontSize = 12);
    ~TextManager();
    SDL_Texture* CreateTextTexture(SDL_Renderer* renderer, const char* text, SDL_Color color);
private:
    TTF_Font* font = nullptr;
};


#endif //SNAKE_GAME_SDL2_TEXTMANAGER_H