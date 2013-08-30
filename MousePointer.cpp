/*
 *  MousePointer.cpp
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett, John Felderhof, Enda McNally.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include "graphics_engine.h"

#include "Physics/CollisionManager.h"
#include "Game.h"
#include "ProcessManager.h"

#include "MousePointer.h"

#define SAFE_DELETE(p)	{if (p)	{ delete (p); (p) = NULL; } }
typedef void (MousePointer::*funcPntr)( struct InputHandler::Mouse * );

MousePointer::MousePointer(std::wstring file_name) {
    loadImage(file_name);

    colour.v1.a = 255;
    colour.v2.a = 255;
    colour.v3.a = 255;
    colour.v4.a = 255;
    colour.v1.r = 255;
    colour.v2.r = 255;
    colour.v3.r = 255;
    colour.v4.r = 255;
    colour.v1.g = 255;
    colour.v2.g = 255;
    colour.v3.g = 255;
    colour.v4.g = 255;
    colour.v1.b = 255;
    colour.v2.b = 255;
    colour.v3.b = 255;
    colour.v4.b = 255;

    /* Make collision mask */
    createCollisionMask();

    clicked = false;
}

MousePointer::~MousePointer() {
}

bool MousePointer::isClicked() {
    return clicked;
}

void MousePointer::click() {
    clicked = true;
}

void MousePointer::unclick( void *arg )
{
    clicked = false;
}

void MousePointer::createCollisionMask() {
// 	mask = new CollisionMask( getWidth(), getHeight() );
// 	for( int i = 0; i < mask->size(); i++ )
// 		mask->mask[i] = false;
// 	mask->mask[0] = true;
}

/* Static functions */
MousePointer* MousePointer::current_mouse;

MousePointer* MousePointer::load(std::wstring file_name) {
    current_mouse = new MousePointer(file_name);
    InputHandler::bindMouseMovement(updatePosition);
    return current_mouse;
}

void MousePointer::unload() {
    InputHandler::unbindMouseMovement();
    delete current_mouse;
}

static void MousePointer::updatePosition(InputHandler::Mouse *mouse) {
    current_mouse->setPosition(mouse->x, mouse->y);
}

