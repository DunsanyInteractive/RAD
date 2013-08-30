/*
 *  Sound_lua.hpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include <iostream>

#include "../LuaEngine.h"

#include "../Sound.h"

static const char *LIB_NAME = "Sound";

static Sound* checkType( lua_State *L )
{
    std::string lib_name;
    void *ud;

    lib_name = LuaEngine::generate_libname( LIB_NAME );
    ud = luaL_checkudata( L, 1, lib_name.c_str() );

    luaL_argcheck( L, ud != NULL, 1, "'Sound' expected" );
    return *(Sound**)ud;
}

static int new_sound( lua_State *L )
{
    size_t l;
    std::string lib_name;
    Sound **ret;

    std::string arg( lua_tolstring( L, -1, &l ) );
    lua_pop( L, 1 );

    ret = (Sound **)lua_newuserdata( L, sizeof( Sound * ) );
    *ret = new Sound( arg );

    lib_name = LuaEngine::generate_libname( LIB_NAME );
    luaL_getmetatable( L, lib_name.c_str() );
    lua_setmetatable( L, -2 );

    return 1;
}

static int delete_sound( lua_State *L )
{
    Sound *sound = checkType( L );

    delete sound;

    return 0;
}

static int play_static( lua_State *L )
{
    size_t length;
    const char *file_name = lua_tolstring( L, -1, &length );
    std::string wfile_name( file_name );

    Sound::Play( wfile_name );

    return 0;
}

static int loop_sound( lua_State *L )
{
    bool arg;
    Sound *sound = checkType( L );

    arg = lua_toboolean( L, -1 );
    sound->setLoop( arg );

    return 0;
}

static int offset( lua_State *L )
{
    int arg;
    Sound *sound = checkType( L );

    arg = lua_tonumber( L, -1 );
    //sound->setOffset( arg );

    return 0;
}

static int pause_sound( lua_State *L )
{
    Sound *sound = checkType( L );

    //sound->pause();

    return 0;
}

static int play( lua_State *L )
{
    Sound *sound = checkType( L );

    sound->play();

    return 0;
}

static int stop( lua_State *L )
{
    Sound *sound = checkType( L );

    sound->stop();

    return 0;
}

static const struct luaL_reg lib_f[] = {
    { "new", new_sound },
    { "delete", delete_sound },
    { "play", play_static },
    { NULL, NULL }
};

static const struct luaL_reg lib_m[] = {
    { "loop", loop_sound },
    { "offset", offset },
    { "pause", pause_sound },
    { "play", play },
    { "stop", stop },
    { "__gc", delete_sound },
    { NULL, NULL }
};

void libsound( lua_State *L )
{
    LuaEngine::openlib( L, LIB_NAME, lib_f, lib_m );

    /* Hook here to run initializing lua code */
    LuaEngine::runfile( "LUA/Sound.lua" );
}
