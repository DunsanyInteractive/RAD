/*
 *  Sprite.hpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "../Game.h"
#include "../LuaEngine.h"

#include "../Sprite.h"

namespace {
const char *LIB_NAME = "Sprite";

static Sprite* checkType( lua_State *L )
{
    std::string lib_name;
    void *ud;

    lib_name = LuaEngine::generate_libname( LIB_NAME );
    ud = lua_touserdata( L, 1 );

    luaL_argcheck( L, ud != NULL, 1, "'Sprite' expected" );
    return static_cast<Sprite *>(*(void **)ud);
}

static int new_sprite( lua_State *L )
{
    std::string lib_name;
    Sprite **ret;

    ret = (Sprite **)lua_newuserdata( L, sizeof( Sprite * ) );
    *ret = new Sprite();

    Game::level->add( *ret );

    lib_name = LuaEngine::generate_libname( LIB_NAME );
    luaL_getmetatable( L, lib_name.c_str() );
    lua_setmetatable( L, -2 );

    return 1;
}

static int image( lua_State *L )
{
    const char* buf;
    Sprite *sprite = checkType( L );

    buf = lua_tostring( L, -1 );
    std::wstring image_file_name( strlen( buf ), L' ' );
    copy( buf, buf + strlen(buf), image_file_name.begin() );

    sprite->loadImage( image_file_name );

    return 0;
}

static int position( lua_State *L )
{
    Sprite *sprite = checkType( L );
    double x = lua_tonumber( L, -2 );
    double y = lua_tonumber( L, -1 );
    lua_pop( L, 2 );

    sprite->setPosition( (float)x, (float)y );

    return 0;
}

static int layer( lua_State *L )
{
    Sprite *sprite = checkType( L );
    sprite->layer = (float)lua_tonumber( L, -1 );
    lua_pop( L, 1 );

    return 0;
}

static int sourceRect( lua_State *L )
{
    Sprite *sprite = checkType( L );
    double left = lua_tonumber( L, -4 );
    double top = lua_tonumber( L, -3 );
    double right = lua_tonumber( L, -2 );
    double bottom = lua_tonumber( L, -1 );

    sprite->setSourceRect((float)left, (float)top, (float)right, (float)bottom);

    return 0;
}

static int size( lua_State *L )
{
    Sprite *sprite = checkType( L );
    double height = lua_tonumber( L, -1 );
    double width = lua_tonumber( L, -2 );

    sprite->setSize((float)width, (float)height);

    return 0;
}

static int visible( lua_State *L )
{
    Sprite *sprite = checkType( L );
    sprite->visible = (int)lua_toboolean( L, -1 );
    return 0;
}

static int delete_obj( lua_State *L )
{
    Sprite* sprite = checkType( L );

    Game::level->remove( sprite );

    delete sprite;

    return 0;
}

static int rotation( lua_State *L )
{
    Sprite *sprite = checkType( L );
    sprite->rotation = (float)lua_tonumber( L, -1);
    return 0;
}

static const struct luaL_reg lib_f[] = {
    { "new", new_sprite },
    { NULL, NULL }
};

static const struct luaL_reg lib_m[] = {
    { "image" , image },
    { "position", position },
    { "sourceRect", sourceRect },
    { "size", size},
    { "layer", layer },
    { "visible", visible },
    { "__gc", delete_obj },
    { "rotation", rotation },
    { NULL, NULL }
};
};

void libsprite( lua_State *L )
{
    LuaEngine::openlib( L, LIB_NAME, lib_f, lib_m );

    /* Hook here to run initializing lua code */
    LuaEngine::runfile( "LUA/Sprite.lua" );
}
