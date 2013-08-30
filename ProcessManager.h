/*
 *  ProcessManager.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett, John Felderhof.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <list>
#include "Sprite.h"

namespace ProcessManager {
void init();
void clean();

void loadProcessList();
void addProcess(Sprite *);
void updateList();
void remove( Sprite * );
void purgeProcessList();

/* Timed function calls */
void processTimedCalls();
void CallIn( double, int );	/* call lua function in 'float' seconds */
void CallIn( double, void (*)(void *), void * );

extern std::list<Sprite *> processList;
};

#endif
