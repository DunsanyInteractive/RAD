/*
 *  Guicon.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef WINDOWS_INPUT_INTERFACE_H
#define WINDOWS_INPUT_INTERFACE_H

#include "../input_interface.h"
#include <iostream>
#define SAFE_DELETE(p)	{if (p)	{ delete (p); (p) = NULL; } }


namespace Input_Interface
{
extern std::queue<struct Input_Event *> event_queue;

//	void clean();
//	void AddInputToQueue(unsigned int, unsigned int, unsigned long);

};

#endif
