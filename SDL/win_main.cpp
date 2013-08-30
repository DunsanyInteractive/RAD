/*
 *  input_interface.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "../graphics_engine.h"
#include "../InputHandler.h"
#include "../Console.h"
// #include "../LuaEngine.h"
// #include "SDL.h"
// #include "../Game.h"
// #include <tchar.h>
// #include <sstream>
// #include <windows.h>
//
// using namespace std;
//
// void game_loop() {
// 		using namespace Game;
//
// 		InputHandler::bindKey( SDLK_c, &Console::enable );
// 		InputHandler::bindKey( SDLK_x, &Game::exit );
//
// 		while( appRunning )
// 		{
// 			update();
// 			display();
// 		}
// }
//
// int main(int argc, char* argv[]) {
// 	if (argc != 2) {
// 		cout << "Usage: ";
// 		cout << argv[0];
// 		cout << " [Script]";
// 		return EXIT_FAILURE;
// 	}
//
// 	//wstringstream wsstr;
// 	//wsstr << argv[1];
// 	//wstring dir = getDirectoryName(wsstr.str());
//
// 	/* Strangely this cases the program to return into the graphics engine to open the file as an image */
// 	//stringstream sstr;
// 	//sstr << getBaseName(wsstr.str());
// 	//std::cout << sstr.str() << std::endl;
// 	//string file = sstr.str();
// 	//wstring wfile = getBaseName(wsstr.str());
// 	//string file = string(wfile.length(), '\x00');
// 	//copy(wfile.begin(), wfile.end(), file.begin());
// 	//cout << file << endl;
//
// 	string target(argv[1]);
//
// 	/* Directory */
// 	wstring dir(target.size(), L'');
// 	size_t pos = target.find_last_of('\\');
// 	copy(target.begin(), target.begin() + pos, dir.begin());
//
// 	/* File */
// 	string file = target.substr(pos + 1);
//
// 	GE::init();
// 	Game::initialize();
// 	::SetCurrentDirectory(dir.c_str());
//
// 	/* Load first level */
// 	LuaEngine::run("LoadLevel('" + file + "')");
// 	game_loop();
// 	//Game::clean();  Buggy and not needed
// 	return EXIT_SUCCESS;
// }
