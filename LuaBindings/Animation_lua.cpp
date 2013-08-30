/*
 *  Animation_lua.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "../Game.h"
#include "../LuaEngine.h"
#include "../ProcessManager.h"

#include "../Animation.h"

// 	static const char *LIB_NAME = "Animation";
//
// 	static Animation* checkType( lua_State *L )
// 	{
// 		std::string lib_name;
// 		void *ud;
//
// 		lib_name = LuaEngine::generate_libname( LIB_NAME );
// 		ud = luaL_checkudata( L, 1, lib_name.c_str() );
//
// 		luaL_argcheck( L, ud != NULL, 1, "'Animation' expected" );
// 		return dynamic_cast<Animation *>( *(Sprite**)ud );
// 	}
//
// 	static int new_animation( lua_State *L )
// 	{
// 		std::string lib_name;
// 		Sprite **ret;
// 		Animation *ani = new Animation();
//
// 		ret = (Sprite **)lua_newuserdata( L, sizeof( Sprite * ) );
// 		*ret = static_cast<Sprite *>( ani );
//
// 		Game::level->add( *ret );
// 		ProcessManager::addProcess( ani );
//
// 		lib_name = LuaEngine::generate_libname( LIB_NAME );
// 		luaL_getmetatable( L, lib_name.c_str() );
// 		lua_setmetatable( L, -2 );
//
// 		return 1;
// 	}
//
// 	static int frame( lua_State *L )
// 	{
// 		Animation* ani = checkType( L );
//
// 		ani->setFrame( (int)lua_tonumber( L, -1 ) );
//
// 		return 0;
// 	}
//
// 	static int frames( lua_State *L )
// 	{
// 		Animation* ani = checkType( L );
//
// 		ani->setFrames( (int)lua_tonumber( L, -1 ) );
//
// 		return 0;
// 	}
//
// 	static int rows( lua_State *L )
// 	{
// 		Animation* ani = checkType( L );
//
// 		ani->setRowDimension( (int)lua_tonumber( L, -2 ), (int)lua_tonumber( L, -1 ) );
//
// 		return 0;
// 	}
//
// 	static int delete_obj( lua_State *L )
// 	{
// 		Animation* ani = checkType( L );
//
// 		ProcessManager::remove( static_cast<Sprite *>( ani ) );
// 		Game::level->remove( static_cast<Sprite *>( ani ) );
// 		delete ani;
//
// 		return 0;
// 	}
//
// 	static const struct luaL_reg lib_f[] = {
// 		{ "new", new_animation },
// 		{ NULL, NULL }
// 	};
//
// 	static const struct luaL_reg lib_m[] = {
// 		{ "frame", frame },
// 		{ "frames", frames },
// 		{ "rowDimensions", rows },
// 		{ "__gc", delete_obj },
// 		{ NULL, NULL }
// 	};
//
// void libanimation( lua_State *L )
// {
// 	LuaEngine::openlib( L, LIB_NAME, lib_f, lib_m );
//
// 	/* Hook here to run initializing lua code */
// 	LuaEngine::runfile( "LUA/Animation.lua" );
// }
