#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

#define TIMER_SECONDS_MIN 10
#define TIMER_SECONDS_MAX 240
#define TIMER_SECONDS_DEFAULT 60

extern void timer_init(int seconds);

#endif /* TIMER_H */
