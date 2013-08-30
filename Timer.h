/*
 *  Timer.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof, Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef TIMER_H
#define TIMER_H

#ifdef USE_SDL
#include <SDL/SDL_timer.h>

namespace boost {
class timer {
    unsigned int started;
public:
    timer() {
        restart();
    }
    void restart() {
        started = SDL_GetTicks();
    }
    double elapsed() {
        return (double)(SDL_GetTicks() - started) / 1000;
    }
};
};
#else
#include "boost/timer.hpp"
#endif

class Timer {
public:
    double dtime;
    bool flag1, dStarted;

    boost::timer dTimer;

    Timer();
    ~Timer();
    bool delay(double time);
    double elapsed();	/* Returns time lapsed in seconds */
    void reset();
};

#endif
