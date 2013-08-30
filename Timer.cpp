/*
 *  Timer.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof, Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include "Timer.h"

Timer::Timer()
{
    dStarted = false;
}

Timer::~Timer()
{

}


//Function to Measure time until a certain amount of time has passed. should be run every loop.
//Intput: Time that it should count up until
bool Timer::delay(double time)
{
    if (!dStarted)
    {
        dTimer.restart();
        dtime = time;
        dStarted = true;
        return false;
    }
    else
    {
        double current = elapsed();
        if (dtime > current)
            return false;
        else
        {
            dStarted = false;
            return true;
        }
    }

}

//returns how much time has passed since timer started.
double Timer::elapsed()
{
    return dTimer.elapsed();
}

//Restarts the timer
void Timer::reset()
{
    dTimer.restart();
}
