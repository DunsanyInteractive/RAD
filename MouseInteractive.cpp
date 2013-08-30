/*
 *  Interactive.cpp
 *  temp
 *
 *  Created by John Felderhof on 10/22/10.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "Physics/CollisionManager.h"
#include "LuaEngine.h"
#include "MousePointer.h"
#include "ProcessManager.h"

#include "MouseInteractive.h"

MouseInteractive::MouseInteractive()
{
    clicked = false;
    on_click = NULL;
    on_mouse_over = NULL;
    mouse_over_running = false;
}

void MouseInteractive::collidedWith( Collidable *arg )
{
    MousePointer *m_p;

    if( m_p = dynamic_cast<MousePointer *>( arg ) )
    {
        if( !mouse_over_running )
        {
            mouse_over_running = true;
            mouseOver();
        }

        if( m_p->isClicked() )
            click();
    }
}

void MouseInteractive::click()
{
    if( on_click )
        LuaEngine::run( on_click->c_str() );
}

void MouseInteractive::mouseOver()
{
    if( on_mouse_over )
    {
        mouse_over_running = true;
        LuaEngine::run( on_mouse_over->c_str() );
        if( mouse_over_check_interval > 0 )
            ProcessManager::CallIn( mouse_over_check_interval, &afterMouseOver, (void *)this );
        else
            ProcessManager::CallIn( CollisionManager::PHYSICS_DELAY, &afterMouseOver, (void *)this );
    }
}

void MouseInteractive::onClick( const char *arg )
{
    if( on_click )
        delete on_click;
    on_click = new std::string( arg );
}

void MouseInteractive::onMouseOver( const char *arg, double arg2 )
{
    if( on_mouse_over )
        delete on_mouse_over;
    on_mouse_over = new std::string( arg );
    mouse_over_check_interval = arg2;
}

void MouseInteractive::afterMouseOver( void *arg )
{
    ((MouseInteractive *)arg)->mouse_over_running = false;
}
