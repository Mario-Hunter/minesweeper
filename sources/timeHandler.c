#include <time.h>
#include "judge.h"

double getTime(time_t time1, time_t time2){
    double seconds = difftime( time1,  time2);
    return seconds;
}

void calculateTime(judge_t *judge){
    time_t currentTime;

    time(&currentTime);
    judge->gameTime += getTime(currentTime, judge->gameStartTime);
    judge->gameStartTime = currentTime;
}
void setTime(time_t *clock){
    time(clock);
}
