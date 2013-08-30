/*
 *  main.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "../graphics_engine.h"
#include "../InputHandler.h"
#include "../Console.h"
#include <SDL/SDL.h>
#include <sstream>
#include <unistd.h>
#include "../LuaEngine.h"
#include "../Game.h"

using namespace std;

void game_loop() {
    using namespace Game;

// 		InputHandler::bindKey( SDLK_c, &Console::enable );
    InputHandler::bindKey( SDLK_ESCAPE, &Game::exit );

    while( appRunning )
    {
        update();
        display();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ";
        cout << argv[0];
        cout << " [Script]";
        return EXIT_FAILURE;
    }

    string target(argv[1]);

    int pos = target.find_last_of('/');

    /* Directory */
    string dir = target.substr(0, pos);

    /* File */
    string file = target.substr(pos + 1);

    GE::init();
    Game::initialize();
    chdir(dir.c_str());

    /* Load first level */
    LuaEngine::run("LoadLevel('" + file + "')");
    game_loop();
    //Game::clean();  Buggy and not needed
    return EXIT_SUCCESS;
}
