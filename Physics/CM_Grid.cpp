/*
 *  CM_Grid.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "../graphics_engine.h"
#include "../window_conf.h"
#include "Vector2.h"

#include "CM_Grid.h"

CM_Grid::CM_Grid( unsigned int w, unsigned int h )
{
    width = w;
    height = h;

    grid = new std::set<Collidable *>[width * height];

    for (int x = 0; x < width; x++)
    {
        for	(int y = 0; y < height; y++)
        {
            get(x, y)->clear();
        }
    }

    // ITERATE THROUGH GRID AND CLEAR ALL SETS.
}

CM_Grid::~CM_Grid()
{
    delete grid;
}

void CM_Grid::add( Collidable *arg )
{
    int x_diff, y_diff;
    Vector2 top_left, bottom_right;
    Vector2 diff( -arg->getWidth()/2,
                  arg->getHeight()/2 );

    top_left = arg->center();
    top_left += diff;
    bottom_right = arg->center() - diff;

    x_diff = WINDOW_WIDTH / width;
    y_diff = WINDOW_HEIGHT / height;
    for( int x = top_left.x/x_diff; x <= bottom_right.x/x_diff; x++ )
        for( int y = -top_left.y/y_diff; y <= -bottom_right.y/y_diff; y++ )
            if( x >= 0 && x < width && y >= 0 && y < height )
                get( x, y )->insert( arg );
}

void CM_Grid::draw()
{
    float x_diff = WINDOW_WIDTH / width;
    float y_diff = WINDOW_HEIGHT / height;

    for( int i = 1; i < width; i++ )
        GE::drawLine( i * x_diff, 0, i * x_diff, -WINDOW_HEIGHT );
    for( int i = 0; i < height; i++ )
        GE::drawLine( 0, -i * y_diff, WINDOW_WIDTH, -i * y_diff );
}

void CM_Grid::remove( Collidable *arg )
{
    std::set<Collidable *>::iterator it;
    for( int i = 0; i < width*height; i++ )
    {
        it = get( i, 0 )->find( arg );
        if( it != get( i, 0 )->end() )
            get(i,0)->erase( it );
    }
}

void CM_Grid::update( Collidable *arg )
{
    remove( arg );
    add( arg );
}

void CM_Grid::calcPotentialCollisions()
{
    std::set<Collidable *> *col;
    std::set<Collidable *>::iterator it;
    std::set<Collidable *>::iterator it2;
    Collidable *last_item;

    for( int x = 0; x < width; x++ )
        for( int y = 0; y < height; y++ )
        {
            col = get(x,y);
            int temp = col->size();
            if( temp < 2 )
                continue;

            it = it2 = col->begin();
            last_item = *(--col->end());
            while( *it != last_item )
            {
                while( ++it2 != col->end() )
                {
                    pot_col_list->push( *it );
                    pot_col_list->push( *it2 );
                }
                it2 = ++it;

            }
        }
}
