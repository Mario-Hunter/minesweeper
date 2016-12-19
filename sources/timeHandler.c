#include <time.h>

void setTime(time_t *clock){
    time(clock);
}
double getTime(time_t time1, time_t time2){
    double seconds = difftime( time1,  time2);
    return seconds;
}
