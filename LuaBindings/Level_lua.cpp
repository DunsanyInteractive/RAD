/*
 *  Level_lua.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "../Game.h"
#include "../LuaEngine.h"

#include "../Level.h"

namespace {
const char *LIB_NAME = "Level";

static Level* checkType( lua_State *L )
{
    std::string lib_name;
    void *ud;

    lib_name = LuaEngine::generate_libname( LIB_NAME );
    ud = luaL_checkudata( L, 1, lib_name.c_str() );

    luaL_argcheck( L, ud != NULL, 1, "'Level' expected" );
    return (*(Level **)ud);
}

static int current( lua_State *L )
{
    std::string lib_name;
    Level **ret;

    ret = (Level **)lua_newuserdata( L, sizeof( Level * ) );
    *ret = Game::level;

    lib_name = LuaEngine::generate_libname( LIB_NAME );
    luaL_getmetatable( L, lib_name.c_str() );
    lua_setmetatable( L, -2 );

    return 1;
}

static int addSprite( lua_State *L )
{
    Level *level = (Level *)checkType( L );
    Sprite *sprite = *(Sprite **)lua_touserdata( L, -1 );
    lua_pop( L, 1 );

    level->add( sprite );

    return 0;
}

static const struct luaL_reg lib_f[] = {
    { "current", current },
    { NULL, NULL }
};

static const struct luaL_reg lib_m[] = {
    { "addSprite", addSprite },
    { NULL, NULL }
};
};

void liblevel( lua_State *L )
{
    LuaEngine::openlib( L, LIB_NAME, lib_f, lib_m );

    /* Hook here to run initializing lua code */
    LuaEngine::runfile( "LUA/Level.lua" );
}
