/*
 *  BoundingSphere.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "BoundingCircle.h"

BoundingCircle::BoundingCircle( float arg )
{
    radius = arg;
}

bool BoundingCircle::overlaps( const BoundingCircle *arg )
{
    float distance = radius + arg->radius;
    return (center - arg->center).squareMagnitude() <= distance*distance;
}

bool BoundingCircle::overlaps( const Vector2 *arg )
{
    return (center - *arg).squareMagnitude() <= radius*radius;
}

float BoundingCircle::greatestDistanceFrom( Vector2 arg )
{
    return (arg - center).magnitude() + radius;
}
