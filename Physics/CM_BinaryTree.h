/*
 *  CM_BinaryTree.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "BTNode.h"
#include "CollisionManager.h"

class CM_BinaryTree : public CollisionManager {
    BTNode *root;

public:
    CM_BinaryTree();
    ~CM_BinaryTree();

    void add( Collidable * );
    void draw();
    void remove( Collidable * );
    void update();
    void update( Collidable * );

    void calcPotentialContacts();
};
