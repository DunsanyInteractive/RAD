/*
 *  CollisionManager.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include <queue>

#include "CollisionManager.h"

double CollisionManager::PHYSICS_DELAY;

CollisionManager::CollisionManager()
{
    pot_col_list = new std::queue<Collidable *>();
    col_list = new std::queue<Collision *>();
}

CollisionManager::~CollisionManager()
{
    while( !pot_col_list->empty() ) {
        delete pot_col_list->front();
        pot_col_list->pop();
    }
    while( !col_list->empty() ) {
        delete col_list->front();
        col_list->pop();
    }
}

void CollisionManager::update()
{
    /* Not WORKING!! Need to update objects here */
    calcPotentialCollisions();

    if( pot_col_list->empty() )
        return;

    Collidable *obj1, *obj2;
    Collision *col;
    do
    {
        obj1 = pot_col_list->front();
        pot_col_list->pop();
        obj2 = pot_col_list->front();
        pot_col_list->pop();
        if( verifyCollision( obj1, obj2 ) )
            col_list->push( new Collision( obj1, obj2 ) );
    } while( !pot_col_list->empty() );

    /* Seperate lists as collision resolution might need it this way in future */
    while( !col_list->empty() )
    {
        col = col_list->front();
        col_list->pop();
        col->objs[0]->collidedWith( col->objs[1] );

        delete col;
    }
}

bool CollisionManager::verifyCollision( Collidable *arg1, Collidable *arg2 )
{
    struct CollisionMask *mask1, *mask2;
    Vector2 top_offset, bottom_offset;
    Vector2 diff;

    diff.x = -(arg2->getWidth() - arg1->getWidth())/2;
    diff.y = (arg2->getHeight() - arg1->getHeight())/2;

    top_offset = arg2->center() - arg1->center(); /* Temp store */
    bottom_offset = top_offset - diff;
    top_offset += diff;

    int x1, y1;
    int x2, y2;
    int height, width;

    if( top_offset.x > 0 )
    {
        x1 = top_offset.x;
        x2 = 0;

        if( bottom_offset.x < 0 )
            width = arg2->getWidth();
        else
            width = arg1->getWidth() - top_offset.x;
    }
    else
    {
        x1 = 0;
        x2 = arg2->getWidth() - top_offset.x;

        if( bottom_offset.x > 0 )
            width = arg1->getWidth();
        else
            width = arg1->getWidth() + bottom_offset.x;
    }

    if( x1 < 0 || x2 < 0 || width < 0 )
        return false;

    if( top_offset.y > 0 )
    {
        y1 = 0;
        y2 = arg2->getHeight() - top_offset.y;

        if( bottom_offset.y < 0 )
            height = arg1->getHeight();
        else
            height = arg1->getHeight() - bottom_offset.y;
    }
    else
    {
        y1 = -top_offset.y;
        y2 = 0;

        if( bottom_offset.y > 0 )
            height = arg2->getHeight();
        else
            height = arg2->getHeight() + bottom_offset.y;
    }

    if( y1 < 0 || y2 < 0 || height < 0 )
        return false;

    mask1 = arg1->getMask();
    mask2 = arg2->getMask();
    for( int y = 0; y < height; y++ )
        for( int x = 0; x < width; x++ )
            if( mask1->at(x1 + x, y1 + y) & mask2->at(x2 + x, y2 + y) )
                return true;

    return false;
}
