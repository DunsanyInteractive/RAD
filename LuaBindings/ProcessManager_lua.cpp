/*
 *  ProcessManager_lua.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "../LuaEngine.h"

#include "../ProcessManager.h"

static const char *LIB_NAME = "ProcessManager";

static int call_in( lua_State *L )
{
    double delay = lua_tonumber( L, -2 );
    int func = luaL_ref( L, LUA_REGISTRYINDEX );

    ProcessManager::CallIn( delay, func );

    return 0;
}

static const struct luaL_reg lib_f[] = {
    { "CallIn", call_in },
    { NULL, NULL }
};

static const struct luaL_reg lib_m[] = {
    { NULL, NULL }
};

void libprocessManager( lua_State *L )
{
    LuaEngine::openlib( L, LIB_NAME, lib_f, lib_m );

    /* Hook here to run initializing lua code */
    LuaEngine::runfile( "LUA/ProcessManager.lua" );
}

