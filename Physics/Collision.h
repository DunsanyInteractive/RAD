/*
 *  Collision.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett, John Felderhof.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef COLLISION_H
#define COLLISION_H

#include <stack>
#include "../Base.h"
#include "../Sprite.h"

class Collision
{
public:
    Collision();
    ~Collision();
    Collision(Sprite* sprite);
    Collision(float top, float left, float bottom, float right);

    /* To be taken out in the future */
    enum Col_Type {
        BUTTON_CLICK,
        MOUSE_OVER,
        MISC
    };

    int col_type;
    Base *object;


    struct {
        float x, y;
    } origin;
    bool colliding, moving;
    struct {
        int width, height;
        bool *bits;
    } bitMask;
    bool checkSpriteCollision(Sprite *sprite);
    bool checkCollision( int, int );
    bool checkCollision(Collision *);
    bool pixelPerfectDetection(Collision *collision);

    /* Better :) */
    static std::stack<Collision *> *findCollision( int, int, Collision * = NULL );
};





#endif
