/*
 *  CM_BinaryTree.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include "CM_BinaryTree.h"

CM_BinaryTree::CM_BinaryTree()
{
    root = NULL;
    BTNode::timer = new Timer();
}

CM_BinaryTree::~CM_BinaryTree()
{
    delete root;
    delete BTNode::timer;
}

void CM_BinaryTree::add( Collidable *arg )
{
    BTNode *new_node = new BTNode( arg );
    new_node->calcCenter();

    if( !root )
        root = new_node;
    else
    {
        root->insert( new_node );
    }
}

void CM_BinaryTree::draw()
{
    if( root )
        root->draw();
}

void CM_BinaryTree::remove( Collidable *arg )
{
    if( !root )
        return;

    if( root->object == arg )
    {
        delete root;
        root = NULL;
    }
    else
        root->remove( arg );
}

void CM_BinaryTree::update( Collidable *arg )
{
    remove( arg );
    add( arg );
}

/***
** Collision related functions
***/
void CM_BinaryTree::calcPotentialContacts()
{
    root->getPotentialContacts( pot_col_list );
}
