/*
 *  CM_Grid.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "CollisionManager.h"

#include <set>

class CM_Grid : public CollisionManager {
    std::set<Collidable *> *grid;
    unsigned int height;
    unsigned int width;

    inline std::set<Collidable *> *get( int x, int y )
    {
        return &grid[ y*width + x ];
    }

public:
    CM_Grid( unsigned int, unsigned int );
    ~CM_Grid();

    void add( Collidable * );
    void draw();
    void remove( Collidable * );
    void update( Collidable * );

    /* Collision detection */
    void calcPotentialCollisions();
};
