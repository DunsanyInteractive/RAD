/*
 *  Collidable.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <iostream>

#include "Vector2.h"

/* Interface for collision system */
struct CollisionMask {
    unsigned int height;
    unsigned int width;
    bool *mask;

    CollisionMask( int w, int h ) {
        width = w;
        height = h;
        mask = new bool[ w * h ];
    }

    bool at( unsigned int x, unsigned int y ) {
        return mask[y*height + x];
    };
    int size() {
        return width * height;
    }
};

class Collidable {
public:
    virtual void collidedWith( Collidable * ) = 0;

    virtual Vector2 center() = 0;
    virtual float getHeight() = 0;
    virtual float getWidth() = 0;

    CollisionMask* getMask() {
        return mask;
    };
protected:
    CollisionMask *mask;
};

#endif
