/*
 *  MouseInteractive_lua.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof on 11/24/10.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#ifndef MOUSE_INTERACTIVE_LUA
#define MOUSE_INTERACTIVE_LUA

#include "../LuaEngine.h"

namespace MouseInteractive_LUA {
extern const char *LIB_NAME;

extern int on_click( lua_State * );
extern int on_mouse_over( lua_State * );

extern const struct luaL_reg lib_m[];
};

#endif
