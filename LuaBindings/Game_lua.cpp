/*
 *  Game_lua.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "../LuaEngine.h"

#include "../Game.h"

static const char *LIB_NAME = "Game";

static int exit_game( lua_State *L )
{
    Game::exit();

    return 0;
}

static int load_level( lua_State *L )
{
    size_t len;
    const char *temp = lua_tolstring( L, -1, &len );
    std::string level(temp);

    Game::loadLevel( level );
    lua_getglobal( L, "Level.current" );
    lua_pcall( L, 0, 1, 0 );

    return 1;
}

static int load_mouse( lua_State *L ) {
    const char *buf = lua_tostring( L, -1 );
    std::wstring image_file( strlen( buf ), L' ' );
    copy( buf, buf + strlen(buf), image_file.begin() );

    Game::loadMouse(image_file);
}

static int unload_mouse( lua_State *L ) {
    Game::unloadMouse();
}

static const struct luaL_reg lib_f[] = {
    { "Exit", &exit_game },
    { "LoadLevel", &load_level },
    { "LoadMouse", &load_mouse },
    { "UnloadMouse", &unload_mouse },
    { NULL, NULL }
};

void libgame( lua_State *L )
{
    luaL_register( L, "Game", lib_f );
    //lua_pushcfunction( L, &load_level );
    //lua_setglobal( L, "LoadLevel" );
    /* Hook here to run initializing lua code */
    LuaEngine::runfile( "LUA/Game.lua" );
}
