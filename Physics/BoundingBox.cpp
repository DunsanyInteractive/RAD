/*
 *  BoundingBox.cpp
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include "BoundingBox.h"


BoundingBox::BoundingBox()
{
}

BoundingBox::~BoundingBox()
{

}

void BoundingBox::setBoundingBox(Vector2 centre, Vector2 bbsize)
{
    center = centre;
    size = bbsize;
}

BoundingBox &BoundingBox::operator=(const BoundingBox &bbox)
{
    center = bbox.center;
    size = bbox.size;
    return *this;
}
