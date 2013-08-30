/*
 *  Console.cpp
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include "Console.h"
#include "LuaEngine.h"
#include "graphics_engine.h"
#include "Font_Handler.h"
#include "input_interface.h"
#include "Game.h"
#include <sstream>
#include <iostream>


namespace Console {

	using namespace II::Key_Codes;
	bool enabled;
	std::stringstream  *input_stream;
	Sprite* console;
	std::list<std::string> history;
	std::list<std::string>::iterator historyIt;
	int history_count, input_pos;


	bool enable_console;
	
	void init()
	{
		enabled = false;
		enable();
		input_pos = 0;
		std::wstring *filename;
		filename = (new std::wstring(L"Assets/Overlay.png"));
		console = new Sprite(0, 0 ,512 ,512, GE::loadImageFromFile(filename));
		SAFE_DELETE(filename);
		console->width = 1280;
		console->height = 512;
		console->layer = 2;
		console->position.setVector(0, 800);
		historyIt = history.end();
		input_stream = new std::stringstream;
		Font_Handler::createString("loading Console..........\nCONSOLE ACTIVATED\n");

		disable();
	}

	void draw_console()
	{
		console->draw();	
	}
	
	void grab_string(std::string arg)
	{
		if( arg[0] == '~' ) {
			disable();
			return;
		}

		std::cout << "CONSOLE OUTPUT :> " << arg << std::endl; 			
		LuaEngine::run( arg );
	}

	void write(int ascii_code)
	{
		switch( ascii_code )
		{
			/* Escape */
			case 96:
			case 27:
				disable();
				break;
			case 13:
			case 10:			//Enter
				{
					if (!input_stream->str().empty())
					{
						Font_Handler::createLetter(ascii_code);
						std::string stringToOutput;
						stringToOutput = input_stream->str();
						grab_string(stringToOutput);
						add_to_history(stringToOutput);
						historyIt = history.end();
						SAFE_DELETE(input_stream);
						input_stream = new std::stringstream;
						input_pos = 0;
					}
				}
				break;
			/* Backspace or delete key */
			case '\b':
				{
					Font_Handler::createLetter(ascii_code);
					std::string temp(input_stream->str());
					if (temp.empty())
					{
						SAFE_DELETE(input_stream);
						input_stream = new std::stringstream;
					}
					else
					{
						if ((int)input_stream->tellp() == 0)
							return;
						else if ((int)input_stream->tellp() < (int)input_stream->str().length() && (int)input_stream->tellp() != -1)
						{
							int pos = input_stream->tellp();
							std::string temp(input_stream->str());
							temp.erase(pos - 1, 1);
							input_stream->str(temp);
							input_stream->seekp(pos - 1);
						}
						else
						{
							std::string s(input_stream->str());
							s.erase(s.end() - 1);
							input_stream->str(s);
							input_stream->seekp(input_stream->str().length());
							input_pos--;
						}
					}
				}
				break;
			default:
					if ((int)input_stream->tellp() < (int)input_stream->str().length() && (int)input_stream->tellp() != -1)
					{
						int pos = input_stream->tellp();
						std::string temp, tempchar;
						temp = input_stream->str();
						tempchar = (char)ascii_code;
						temp.insert(pos, tempchar);
						input_stream->str(temp);
						input_stream->seekp(pos + 1);
						Font_Handler::createLetter(ascii_code);
					}
					else
					{
						Font_Handler::createLetter(ascii_code);
						*input_stream << (char)ascii_code;
						input_pos++;
					}
		}
	}

	void action(const int ascii_code)
	{
		using namespace II::Key_Codes;
		switch(ascii_code)
		{
		case UP:
			if (historyIt != history.begin() && !history.empty())
			{	
				historyIt--;
				Font_Handler::deleteLine();
				SAFE_DELETE(input_stream);
				input_stream = new std::stringstream;
				writeLine(*historyIt);
			}
			else
			{
				historyIt = history.end();
				Font_Handler::deleteLine();
				SAFE_DELETE(input_stream);
				input_stream = new std::stringstream;
			}
			break;
		
		case (DOWN):
			if (historyIt != history.end() && !history.empty())
			{	
				Font_Handler::deleteLine();
				SAFE_DELETE(input_stream);
				input_stream = new std::stringstream;
				writeLine(*historyIt);
				historyIt++;
			}
			else
			{
				historyIt = history.begin();
				Font_Handler::deleteLine();
				SAFE_DELETE(input_stream);
				input_stream = new std::stringstream;
			}
			break;

		case LEFT:
			{
				int pos;
				pos = input_stream->tellp();
				if (pos > 0)
				{
					input_stream->seekp(pos - 1);
					Font_Handler::cursor->position.x -= Font_Handler::cursor->width;
				}
				break;
			}

		case RIGHT:
			{
				int pos;
				pos = input_stream->tellp();
				if (pos < (int)input_stream->str().length() && pos != -1)
				{
					input_stream->seekp(pos + 1);
					Font_Handler::cursor->position.x += Font_Handler::cursor->width;
				}
				break;
			}
		}
		
	}
	
	void enable()
	{
		if( !enabled )
		{			
			InputHandler::bindText( &Console::write );
			InputHandler::bindKeyConsole(&Console::action);
			Game::mode = CONSOLE;
			
			enabled = true;
		}
	}
	
	void disable()
	{
		if( enabled )
		{
			InputHandler::unbindText();
			InputHandler::unbindKeyConsole();
			Game::mode = GAME;
			
			enabled = false;
		}
	}

	void clean()
	{
		SAFE_DELETE(input_stream);
		SAFE_DELETE(console);
	}

	void add_to_history(std::string history_string)
	{
		if (history_count <= HISTORY_LIMIT)
		{
			history_count++;
			history.push_back(history_string);
		}
		else
		{
			history.pop_front();
			history.push_back(history_string);
		}
	}
	void writeLine(std::string arg)
	{
		for (int i = 0; i < (int)arg.length(); i++)
			write((int)arg[i]);
	}
};