//
// Created by luisg on 06/10/2025.
//

#include "entities/Score.h"

Score::Score(int pointsPerAchievement){
    points = 0;
    pointsToScore = pointsPerAchievement;
}

void Score::Increase(){
    points += pointsToScore;
}

void Score::Reset(){
    points = 0;
}

void Score::Rebuild(int newPoints){
    pointsToScore = newPoints;
    Reset();
}
