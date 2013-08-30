/*
 *  BoundingBox.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "Bounding.h"
#include "Vector2.h"

class BoundingBox : public Bounding {
public:
    BoundingBox();
    ~BoundingBox();

    void setBoundingBox(const Vector2 centre, const Vector2 bbsize);
    BoundingBox &operator=(const BoundingBox &);
    Vector2 size;
};

#endif
