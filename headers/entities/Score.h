//
// Created by luisg on 06/10/2025.
//

#ifndef SNAKE_GAME_SDL2_SCORE_H
#define SNAKE_GAME_SDL2_SCORE_H


class Score {

public:
    Score(int pointsPerAchievement);
    void Increase();
    void Reset();
    void Rebuild(int newPoints);

    int GetPoints() const{
        return points;
    }

private:
    int pointsToScore;
    int points;


};


#endif //SNAKE_GAME_SDL2_SCORE_H