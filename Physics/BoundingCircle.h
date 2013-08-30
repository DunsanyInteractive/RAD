/*
 *  BoundingCircle.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */
#ifndef BOUNDING_H
#define BOUNDING_H

#include "Bounding.h"

class BoundingCircle : public Bounding {
public:
    BoundingCircle( float = 0 );

    float getSize() {
        return radius;
    }
    float greatestDistanceFrom( Vector2 arg );

    bool overlaps( const BoundingCircle * );
    bool overlaps( const Vector2 * );

    float radius;
};

#endif
