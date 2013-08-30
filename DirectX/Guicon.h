/*
 *  Guicon.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef __GUICON_H__
#define __GUICON_H__
#ifdef _DEBUG

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
};


int luaopen_myprint(lua_State *L);
static int l_print(lua_State *L);
void RedirectIOToConsole();

#endif
#endif
/* End of File */
