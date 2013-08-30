/*
 *  CollisionManager.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <queue>

#include "../Timer.h"
#include "Collidable.h"

class CollisionManager {
protected:
    struct Collision {
        Collidable *objs[2];

        Collision( Collidable *arg1, Collidable *arg2 )
        {
            objs[0] = arg1;
            objs[1] = arg2;
        }
    };

    std::queue<Collidable *> *pot_col_list;
    std::queue<struct Collision *> *col_list;

public:
    CollisionManager();
    ~CollisionManager();

    static double PHYSICS_DELAY;

    /* Bounding related functions */
    virtual void add( Collidable * ) = 0;
    virtual void draw() = 0;
    virtual void remove( Collidable * ) = 0;
    virtual void update( Collidable * ) = 0;

    /* Collision detection */
    virtual void calcPotentialCollisions() {};
    void update();

    bool verifyCollision( Collidable *, Collidable * );
};

#endif
