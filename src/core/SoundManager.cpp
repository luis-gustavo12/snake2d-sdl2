//
// Created by luisg on 06/10/2025.
//

#include "core/SoundManager.h"

#include <iostream>

void SoundManager::Load(const char* filePath, ESoundType soundType, std::string index){

    switch (soundType){
    case ESoundType::MP3: {
        Mix_Music* mp3 = Mix_LoadMUS(filePath);
        if (!mp3){
            std::cout << "Error: " << Mix_GetError() << "\n";
            return;
        }
        musicData.emplace(index,mp3);
        break;
    }
    case ESoundType::WAV: {
        Mix_Chunk* chunk = Mix_LoadWAV(filePath);
        if (!chunk){
            std::cout << "Error: " << Mix_GetError() << "\n";
            return;
        }
        musicData.emplace(index, chunk);
        break;
    }
    default:{
        return;
    }
    }

}

SoundManager::~SoundManager(){

    for (auto const& [key, soundVariant] : musicData){
        std::visit([](auto* sound){
            if constexpr (std::is_same_v<decltype(sound), Mix_Music*>){
                Mix_FreeMusic(sound);
            }
            else if constexpr (std::is_same_v<decltype(sound), Mix_Chunk*>){
                Mix_FreeChunk(sound);
            }
        }, soundVariant);
    }

}

void SoundManager::PlayContinuously(std::string index){

    auto indexValue = musicData.find(index);
    if (indexValue == musicData.end()){
        std::cout << "Value " << index << " not found!!\n";
        return;
    }

    auto variant = indexValue->second;
    std::visit([](auto*sound) {
        if constexpr (std::is_same_v<decltype(sound), Mix_Music*>){
            Mix_PlayMusic(sound, -1);
        }
        else if constexpr (std::is_same_v<decltype(sound), Mix_Chunk*>){
            Mix_PlayChannel(-1, sound, -1);
        }
    }, variant);

}

void SoundManager::PlayOnce(std::string index) {

    auto indexValue = musicData.find(index);

    if (indexValue == musicData.end()){
        std::cout << "Not found: " << index << "\n";
        return;
    }

    auto variant = indexValue->second;
    std::visit([](auto*sound) {
        if constexpr (std::is_same_v<decltype(sound), Mix_Music*>){
            Mix_PlayMusic(sound, 0);
        }
        else if constexpr (std::is_same_v<decltype(sound), Mix_Chunk*>){
            Mix_PlayChannel(-1, sound, 0);
        }
    }, variant);


}





