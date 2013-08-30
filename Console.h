/*
 *  Console.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef CONSOLE_H
#define CONSOLE_H

#include "Sprite.h"

#define SAFE_DELETE(p)	{if (p)	{ delete (p); (p) = NULL; } }
#define HISTORY_LIMIT 50

namespace Console {

	extern bool enabled;
	extern std::stringstream *input_stream;
	extern Sprite* console;
	extern std::list<std::string> history;
	extern int history_count, input_pos;
	void writeLine(std::string arg);
	void add_to_history(std::string);
	void grab_string(std::string arg);
	void init();
	void action();
	void draw_console();
	void write(int ascii_code);
	void action(const int ascii_code);

	void enable();
	void disable();

	void clean();
};

#endif