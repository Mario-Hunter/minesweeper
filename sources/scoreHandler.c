#include <math.h>

#include "judge.h"
#include "graph.h"
int getScore(judge_t *judge){
    time_t currentTime;

    time(&currentTime);
    judge->gameTime = getTime(currentTime, judge->gameStartTime);
    judge->gameScore = pow(judge->grid->width,4)*pow(judge->grid->height,4)/(judge->gameTime*judge->moves);
    return judge->gameScore;
}
