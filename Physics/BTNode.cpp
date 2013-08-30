/*
 *  BTNode.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include <cstdlib>
#include <cmath>
#include "../graphics_engine.h"
#include "../Game.h"
#include "CollisionManager.h"

#include "BTNode.h"

Timer *BTNode::timer;

BTNode::BTNode( Collidable *arg )
{
    parent = NULL;
    left = NULL;
    right = NULL;

    object = arg;
    calcCenter();
    calcBoundingArea();
}
BTNode::~BTNode()
{
    if( parent )
    {
        BTNode *sibling;
        if( this == parent->left )
            sibling = parent->right;
        else
            sibling = parent->left;

        parent->object = sibling->object;
        parent->left = sibling->left;
        parent->right = sibling->right;

        if( sibling->left )
            sibling->left->parent = parent;
        if( sibling->right )
            sibling->right->parent = parent;

        sibling->parent = NULL;
        sibling->left = NULL;
        sibling->right = NULL;
        delete sibling;

        parent->calcCenter();
        parent->calcBoundingArea();
    }

    if( left )
    {
        left->parent = NULL;
        delete left;
    }
    if( right )
    {
        right->parent = NULL;
        delete right;
    }
}

void BTNode::operator=( const BTNode &arg )
{
    /* If changing this, take into consideration delete function */
    object = arg.object;
    parent = arg.parent;
    left = arg.left;
    right = arg.right;

    center = arg.center;
    radius = arg.radius;
}

void BTNode::draw( int depth )
{
    depth += 1;
    if( !isLeaf() )
    {
        left->draw( depth );
        right->draw( depth );
    }

    if( isLeaf() )
        center = object->center();

    if( depth == ((int)timer->elapsed() % 7 + 1) )
        GE::drawCircle( center.x, center.y, radius, 1, 0 );
    else
        GE::drawCircle( center.x, center.y, radius, 0, 1 );
}

using namespace std;
void BTNode::calcBoundingArea()
{
    if( isLeaf() )
    {
        float width = object->getWidth();
        float height = object->getHeight();
        radius = sqrt(width*width + height*height)/2;
    }
    else
        radius = ((left->center - right->center).magnitude() + left->radius + right->radius)/2;
}

float BTNode::getGrowth( BoundingCircle *arg )
{
    return (arg->center - center).magnitude() + arg->radius - radius;
}

void BTNode::getPotentialContacts( std::queue<Collidable *> *list )
{
    if( isLeaf() )
        return;
    else
    {
        left->getPotentialContacts( list );
        right->getPotentialContacts( list );
    }

    left->getPotentialContactsWith( right, list );
}

void BTNode::insert( BTNode *arg )
{
    using namespace std;
    if( isLeaf() )
    {
        /* Create new parent */
        BTNode *new_node = new BTNode();
        *new_node = *this;
        new_node->parent = this;
        arg->parent = this;

        object = NULL;
        left = arg;
        right = new_node;
    }
    else
    {
        if(left->getGrowth( arg ) <= right->getGrowth( arg ))
            left->insert( arg );
        else
            right->insert( arg );
    }

    calcCenter();
    calcBoundingArea();
}

void BTNode::print()
{
    std::cout << this << ':' << center.x << ':' << center.y << ':' << radius << ':' << left << ':' << right << std::endl;
    if( left )
        left->print();
    if( right )
        right->print();
}

bool BTNode::remove( Collidable *arg )
{
    if( object == arg )
    {
        delete this;
        return true;
    }
    else if( isLeaf() )
        return false;
    else if( left->remove( arg ) || right->remove( arg ) )
    {
        return true;
        calcCenter();
        calcBoundingArea();
    }
    return false;
}

void BTNode::getPotentialContactsWith( BTNode *arg, std::queue<Collidable *> *list )
{
    if( !overlaps( arg ) )
        return;

    if( isLeaf() && arg->isLeaf() )
    {
        list->push( this->object );
        list->push( arg->object );
        return;
    }

    if( arg->isLeaf() || (!isLeaf() && getSize() >= arg->getSize()) )
    {
        left->getPotentialContactsWith( arg, list );
        right->getPotentialContactsWith( arg, list );
    }
    else
    {
        getPotentialContactsWith( arg->left, list );
        getPotentialContactsWith( arg->right, list );
    }
}

void BTNode::calcCenter()
{
    if( isLeaf() )
        center = object->center();
    else
    {
        Vector2 temp;
        float mag;
        temp = left->center - right->center;
        mag = temp.magnitude();
        if( mag )
        {
            center.x = (left->center.x + left->radius*temp.x/mag + right->center.x - right->radius*temp.x/mag)/2;
            center.y = (left->center.y + left->radius*temp.y/mag + right->center.y - right->radius*temp.y/mag)/2;
        }
        else
            center = left->center;
    }
}

