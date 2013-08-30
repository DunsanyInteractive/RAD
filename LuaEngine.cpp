/*
 *  LuaEngine.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include <iostream>
#include <sstream>
#include "Console.h"
#include "Game.h"
#include "Font_Handler.h"
#include "LuaBindings/libs.h"

#include "LuaEngine.h"

namespace LuaEngine {
const char *LIB_NAME = "Game";
lua_State *state;

void init()
{
    lua_State *L = lua_open();
    if (state == NULL) {
        print("Can't open LUA state!");
        Game::exit();
    }
    init(L);
}

void init(lua_State *L)
{
    state = L;

    /* Create table to hold classes in Game */
    run( "ClassTable = {}" );

    /* Use this function for LUA 5.1 */
    luaL_openlibs( state );

    /* Load local libraries */
    libgame( state );
    libprocessManager( state );
    liblevel( state );
    libsound( state );
    libsprite( state );
// 		libanimation( state );
// 		libbutton( state );
}

void clean()
{
    lua_close(state);
}

string generate_libname( string name )
{
    ostringstream temp_stream;

    temp_stream << LIB_NAME << '.' << name;

    return temp_stream.str();
}

void inheriteFrom( lua_State *L, string object_name, const struct luaL_reg array_m[] )
{
    string lib_name = generate_libname( object_name );
    luaL_getmetatable( L, lib_name.c_str() );
    luaL_openlib( L, NULL, array_m, 0 );
}

void openlib( lua_State *L, string object_name, const struct luaL_reg array_f[], const struct luaL_reg array_m[] )
{
    string lib_name;

    lib_name = generate_libname( object_name );
    luaL_newmetatable( L, lib_name.c_str() );

    lua_pushstring( L, "__index" );
    lua_pushvalue( L, -2 );
    lua_settable( L, -3 );
    luaL_openlib( L, NULL, array_m, 0 );
    luaL_openlib( L, object_name.c_str(), array_f, 0 );

    /* Add class variable */
    lua_getglobal( L, object_name.c_str() );
    lua_pushstring( L, "class" );
    luaL_getmetatable( L, lib_name.c_str() );
    lua_settable( L, -3 );
    lua_pop( L, 3 );

    /* Add class name to metatable */
    luaL_getmetatable( L, lib_name.c_str() );
    lua_pushstring( L, "class_name" );
    lua_pushstring( L, object_name.c_str() );
    lua_settable( L, -3 );
}

void print( const char *arg )
{
// 		if( Console::enabled )
// 		{
// 			string s( arg );
// 			s += '\n';
// 			Font_Handler::createString( s );
// 			std::cout << "LUA OUTPUT     :> " << s;
// 		}
}

void call_and_unref( int func )
{
    lua_rawgeti( state, LUA_REGISTRYINDEX, func );

    if( lua_pcall( state, 0, 0, 0 ) )
    {
        std::cout << lua_tostring( state, -1 )  << std::endl;
        lua_pop( state, -1 );
    }

    luaL_unref( state, LUA_REGISTRYINDEX, func );
}

void collect_garbage()
{
    lua_gc( state, LUA_GCCOLLECT, 0 );
}

void run( string arg )
{
    int error;

    error = luaL_loadbuffer( state, arg.c_str(), arg.length(), "Line" ) || lua_pcall( state, 0, 0, 0 );
    if( error )
    {
        /* Throw error should go here instead */
        print( lua_tostring( state, -1 ) );
        lua_pop( state, 1 );
    }
}

void runfile( string file )
{
    int error = luaL_dofile( state, file.c_str() );
    if (error) {
        /* Throw error should go here instead */
        print( lua_tostring( state, -1 ) );
        lua_pop( state, 1 );
    }
}
};
