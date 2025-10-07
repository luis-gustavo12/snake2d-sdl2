//
// Created by luisg on 06/10/2025.
//

#ifndef SNAKE_GAME_SDL2_SOUNDMANAGER_H
#define SNAKE_GAME_SDL2_SOUNDMANAGER_H
#include <map>
#include <memory>
#include <SDL_mixer.h>
#include <string>
#include <variant>

enum ESoundType {
    WAV, MP3 // TODO: Add more types
};

class SoundManager {
public:
    void Load(const char* filePath, ESoundType soundType, std::string index);
    ~SoundManager();
    SoundManager() = default;
    void PlayContinuously(std::string index);
    void PlayOnce(std::string index);
private:

    std::map<std::string, std::variant<Mix_Music*, Mix_Chunk*>> musicData;


};


#endif //SNAKE_GAME_SDL2_SOUNDMANAGER_H