/*
 *  Button_lua.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "MouseInteractive_lua.h"
#include "../LuaEngine.h"
#include "../Game.h"
#include "../Button.h"
#include "../ProcessManager.h"

// namespace {
// 	const char *LIB_NAME = "Button";
//
// 	static Button* checkType( lua_State *L )
// 	{
// 		std::string lib_name;
// 		void *ud;
//
// 		lib_name = LuaEngine::generate_libname( LIB_NAME );
// 		ud = luaL_checkudata( L, 1, lib_name.c_str() );
//
// 		luaL_argcheck( L, ud != NULL, 1, "'Button' expected" );
// 		return dynamic_cast<Button *>(*(Sprite**)ud);
// 	}
//
// 	static int new_button( lua_State *L )
// 	{
// 		std::string lib_name;
// 		Sprite **ret;
// 		Button *but = new Button();
//
// 		ret = (Sprite **)lua_newuserdata( L, sizeof( Button * ) );
// 		*ret = static_cast<Sprite *>( but );
//
// 		Game::level->add( *ret );
// 		ProcessManager::addProcess( but );
// 		Game::level->collision_manager->add( but );
//
// 		lib_name = LuaEngine::generate_libname( LIB_NAME );
// 		luaL_getmetatable( L, lib_name.c_str() );
// 		lua_setmetatable( L, -2 );
//
// 		return 1;
// 	}
//
// 	static int delete_obj( lua_State *L )
// 	{
// 		Button *button = checkType( L );
//
// 		ProcessManager::remove( button );
// 		Game::level->collision_manager->remove( button );
// 		Game::level->remove( button );
//
// 		delete button;
//
// 		return 0;
// 	}
//
// 	static const struct luaL_reg lib_f[] = {
// 		{ "new", new_button },
// 		{ NULL, NULL }
// 	};
//
// 	static const struct luaL_reg lib_m[] = {
// 		{ "__gc", delete_obj },
// 		{ NULL, NULL }
// 	};
// };
//
// void libbutton( lua_State *L )
// {
//
// 	LuaEngine::openlib( L, LIB_NAME, lib_f, lib_m );
// 	LuaEngine::inheriteFrom( L, LIB_NAME, MouseInteractive_LUA::lib_m );
// 	LuaEngine::runfile( "LUA/Button.lua" );
// }
