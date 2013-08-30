/*
 *  Interactive.h
 *  temp
 *
 *  Created by John Felderhof on 10/22/10.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "Physics/Collidable.h"

class MouseInteractive : public Collidable {
    bool clicked;
    bool mouse_over_running;

    double mouse_over_check_interval;

    std::string *on_click;
    std::string *on_mouse_over;

public:
    MouseInteractive();

    void collidedWith( Collidable * );

    void click();
    void unclick();
    void mouseOver();

    /* Configuration functions */
    void onClick( const char * );
    void onMouseOver( const char *, double = 0 );

    static void afterMouseOver( void * );
};

#endif
