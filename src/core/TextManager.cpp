//
// Created by luisg on 06/10/2025.
//

#include "core/TextManager.h"


#include "SDL_ttf.h"

std::unique_ptr<TextManager> TextManager::Create(const char* filePath, int fontSize){

    if (TTF_Init() == -1){
        TTF_ERROR_MSG;
        return nullptr;
    }

    auto manager = std::make_unique<TextManager>();

    manager->font = TTF_OpenFont(filePath, fontSize);

    if (!manager->font){
        TTF_ERROR_MSG;
        return nullptr;
    }

    return manager;
}

TextManager::~TextManager(){
    if (font)
        TTF_CloseFont(font);
    TTF_Quit();
}

SDL_Texture* TextManager::CreateTextTexture(SDL_Renderer* renderer, const char* text, SDL_Color color){

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);
    if (!textSurface){
        TTF_ERROR_MSG;
        return nullptr;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture){
        std::cout << "Error: " << SDL_GetError() << "\n";
        SDL_FreeSurface(textSurface);
        return nullptr;
    }

    SDL_FreeSurface(textSurface);

    return textTexture;

}
