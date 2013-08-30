/*
 *  Bounding.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#ifndef BOUNDING_CIRCLE_H
#define BOUNDING_CIRCLE_H

#include "Vector2.h"

class BoundingCircle;

class Bounding {
public:
    virtual float greatestDistanceFrom( Vector2 ) = 0;
    virtual bool overlaps( const BoundingCircle * ) = 0;
    virtual bool overlaps( const Vector2 * ) = 0;

    Vector2 center;
};

#endif
