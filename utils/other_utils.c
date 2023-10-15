#include <time.h>
#include <sys/time.h>
#include "other_utils.h"

static void _delayMicrosecondsHard(unsigned int howLong) {
    struct timeval tNow, tLong, tEnd;

    gettimeofday(&tNow, NULL);
    tLong.tv_sec = howLong / 1000000;
    tLong.tv_usec = howLong % 1000000;
    timeradd(&tNow, &tLong, &tEnd);

    while (timercmp(&tNow, &tEnd, <))
        gettimeofday(&tNow, NULL);
}

void rov_delay(unsigned int ms)
{
    struct timespec sleeper, dummy;

    sleeper.tv_sec = (time_t) (ms / 1000);
    sleeper.tv_nsec = (long) (ms % 1000) * 1000000;

    nanosleep(&sleeper, &dummy);
}

void rov_delayMicroseconds(unsigned int us) {
    struct timespec sleeper;
    unsigned int uSecs = us % 1000000;
    unsigned int wSecs = us / 1000000;

    if (us == 0)
        return;
    else if (us < 100)
        _delayMicrosecondsHard(us);
    else {
        sleeper.tv_sec = wSecs;
        sleeper.tv_nsec = (long) (uSecs * 1000L);
        nanosleep(&sleeper, NULL);
    }
}
