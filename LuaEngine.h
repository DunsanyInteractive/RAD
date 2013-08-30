/*
 *  LuaEngine.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef LUAENGINE_H
#define LUAENGINE_H

extern "C"
{
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
};

#include <string>

namespace LuaEngine {
using namespace std;

void init();
void init(lua_State *L);
void clean();

string generate_libname( string );
void inheriteFrom( lua_State *, string, const struct luaL_reg[] );
void openlib( lua_State *, string, const struct luaL_reg[], const struct luaL_reg[] );

void print( const char * );

void call_and_unref( int );
void collect_garbage();

void run( string );
void runfile( string );

extern lua_State *state;
extern const char *LIB_NAME;
};

#endif
