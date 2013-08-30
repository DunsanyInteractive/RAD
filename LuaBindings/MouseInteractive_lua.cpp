/*
 *  MouseInteractive_lua.cpp
 *  temp
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "../LuaEngine.h"
#include "../Sprite.h"

#include "../MouseInteractive.h"
#include "MouseInteractive_lua.h"

namespace MouseInteractive_LUA {
// 	const char *LIB_NAME  = "MouseInteractive";
// 	const struct luaL_reg lib_m[] = {
// 		{ "onClick", on_click },
// 		{ "onMouseOver", on_mouse_over },
// 		{ NULL, NULL }
// 	};
//
// 	inline MouseInteractive *gettype( lua_State *L )
// 	{
// 		return dynamic_cast<MouseInteractive *>(*(Sprite **)lua_touserdata( L, 1 ));
// 	}
//
// 	int on_click( lua_State *L )
// 	{
// 		size_t l;
// 		MouseInteractive *mi = gettype( L );
//
// 		mi->onClick( lua_tolstring( L, -1, &l ) );
//
// 		return 0;
// 	}
//
// 	int on_mouse_over( lua_State *L )
// 	{
// 		size_t l;
// 		MouseInteractive* mi = gettype( L );
// 		mi->onMouseOver( lua_tolstring( L, -2, &l ), lua_tonumber( L, -1 ) );
//
// 		return 0;
// 	}
};
