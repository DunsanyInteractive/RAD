/*
 *  BTNode.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */
#ifndef BTNODE_H
#define BTNODE_H

#include <queue>

#include "../Timer.h"
#include "BoundingCircle.h"
#include "Collidable.h"

class BTNode : public BoundingCircle {
    BTNode *parent;
    BTNode *left;
    BTNode *right;

public:
    BTNode() : BoundingCircle(0), object(0), parent(0), left(0), right(0) {};
    BTNode( Collidable * );
    ~BTNode();

    void operator=( const BTNode& );

    void draw( int = 0 );
    float getGrowth( BoundingCircle * );
    void calcBoundingArea();
    bool isLeaf() {
        return object != NULL;
    };

    void getPotentialContacts( std::queue<Collidable *> * );

    void insert( BTNode * );
    bool remove( Collidable * );
    void print();

    Collidable* object;

    static Timer *timer;

private:
    bool childOf( BTNode * );
    void getPotentialContactsWith( BTNode *, std::queue<Collidable *> * );

public:
    void calcCenter();
};

#endif
