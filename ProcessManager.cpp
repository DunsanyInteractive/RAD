/*
 *  ProcessManager.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof, Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#include <queue>
#include "LuaEngine.h"
#include "Timer.h"
#include "ProcessManager.h"


namespace ProcessManager {
Timer *pm_timer;

const double PHYSICS_DELAY = 0.3;
std::list<Sprite *> processList;

/* Timed call function for lua */
struct T_Func {
    float delay;
    void (*c_func)(void *);
    int func;
    void *arg;
    bool operator<(const T_Func& x) const {
        return delay > x.delay;
    }
};
std::priority_queue<T_Func> func_queue;

void init()
{
    pm_timer = new Timer();
}

void clean()
{
    delete pm_timer;

    while( !func_queue.empty() )
        func_queue.pop();
}

void addProcess(Sprite *process)
{
    processList.push_back(process);
}

void updateList()
{
    std::list<Sprite *>::iterator iter;
    iter = processList.begin();
    while (iter != processList.end())
    {
        Sprite *obj = (*iter);
        //obj->update();
        iter++;
    }
}

void remove( Sprite *sprite )
{
    processList.remove( sprite );
}

void purgeProcessList()
{
    processList.clear();
}

void processTimedCalls()
{
    while( !func_queue.empty() && func_queue.top().delay < pm_timer->elapsed() )
    {
        const struct T_Func *t = &func_queue.top();

        if( t->c_func )
            t->c_func( t->arg );
        else
            LuaEngine::call_and_unref( func_queue.top().func );
        func_queue.pop();
    }
}

void CallIn( double time_delay, int func )
{
    T_Func temp;
    temp.delay = pm_timer->elapsed() + time_delay;
    temp.c_func = NULL;
    temp.func = func;

    func_queue.push( temp );
}

void CallIn( double time_delay, void (*func)(void *), void *arg )
{
    T_Func temp;
    temp.delay = pm_timer->elapsed() + time_delay;
    temp.c_func = func;
    temp.arg = arg;

    func_queue.push( temp );
}
};

