/*
 *  Collision.cpp
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include "../ProcessManager.h"

#include "Collision.h"

Collision::Collision()
{
    col_type = MISC;
    object = NULL;
//	boundingbox.setBoundingBox(0, 0, 0, 0);
}

Collision::Collision(Sprite* sprite)
{
    col_type = MISC;

    //boundingBox boundingbox;
//	boundingbox.setBoundingBox(sprite->position.y, sprite->position.x, (sprite->position.y - sprite->height), (sprite->position.x + sprite->width));
//	colliding = false;
//	bitMask.height = (int)sprite->height;
//	bitMask.width = (int)sprite->width;
//	bitMask.bits = GE::createBitmask(sprite);
//	origin.x = (sprite->width / 2);
//	origin.y = (sprite->height / 2);
//	moving = false;
}
Collision::Collision(float top, float left, float bottom, float right)
{
//	boundingbox.setBoundingBox(top, left, bottom, right);
//	bitMask.height = 0;
//	bitMask.width = 0;
//	bitMask.bits = NULL;
//	colliding = false;
//	col_type = MISC;
}

Collision::~Collision()
{

}


bool Collision::checkSpriteCollision(Sprite *sprite)
{
//	if ((boundingbox.left <= (sprite->position.x + sprite->width)) && (boundingbox.top <= (sprite->position.y + sprite->height)) && (boundingbox.right >= (sprite->position.x)) && (boundingbox.bottom >= (sprite->position.y)))
//		return true;
//	else
    return false;
}

/* Should include pixel perfect collision */
bool Collision::checkCollision( int x_pos, int y_pos )
{
//	if( boundingbox.left <= x_pos && boundingbox.right >= x_pos
//			&& boundingbox.bottom <= y_pos && boundingbox.top >= y_pos )
//		return true;
//	else
    return false;
}

bool Collision::checkCollision(Collision *collision)
{
//	if ((boundingbox.left <= collision->boundingbox.right) && (boundingbox.top >= collision->boundingbox.bottom) && (boundingbox.right >= collision->boundingbox.left) && (boundingbox.bottom <= collision->boundingbox.top))
//		return true;
//	else
    return false;
}

//uses the bitmap texture to determine if a collision has occured to the pixel level
bool Collision::pixelPerfectDetection(Collision *sCollision)
{
    /*	BoundingBox A, B, overlapA, overlapB;
    	if (boundingbox.left <= sCollision->boundingbox.left)
    	{
    		A = boundingbox;
    		B = sCollision->boundingbox;
    	}
    	else
    	{
    		A = sCollision->boundingbox;
    		B = boundingbox;
    	}
    	if (A.right >= B.right)
    	{
    		if (A.top < B.top)
    		{
    			overlapA.top = A.top;
    			overlapA.left = B.left;
    			overlapA.right = B.right;
    			overlapA.bottom = A.bottom;
    			overlapB = overlapA;
    		}
    		else if (A.bottom > B.bottom)
    		{
    			overlapA.top = B.top;
    			overlapA.left = B.left;
    			overlapA.right = B.right;
    			overlapA.bottom = A.bottom;

    			overlapB = overlapA;
    		}
    		else if ((B.top > A.top) && (B.bottom < A.bottom))
    		{
    			overlapA.top = A.top;
    			overlapA.bottom = A.bottom;
    			overlapA.left = B.left;
    			overlapA.right = B.right;

    			overlapB = overlapA;
    		}
    		else
    		{
    			overlapA = B;
    			overlapB = B;
    		}
    	}

    	else if (B.right > A.right)
    	{
    		if (B.top > A.top)
    		{
    			overlapA.top = A.top;
    			overlapA.bottom = B.bottom;
    			overlapA.left = B.left;
    			overlapA.right = A.right;

    			overlapB = overlapA;

    		}
    		else if (B.top > A.bottom)
    		{
    			overlapA.top = B.top;
    			overlapA.left = B.left;
    			overlapA.bottom = A.bottom;
    			overlapA.right = A.right;

    			overlapB = overlapA;

    		}
    		else if ((B.top > A.top) && (B.bottom < A.bottom))
    		{
    			overlapA = A;
    			overlapA.left = B.left;

    			overlapB = overlapA;

    		}
    		else
    		{
    			overlapA.left = B.left;
    			overlapA.top = B.top;
    			overlapA.right = A.right;
    			overlapA.bottom = B.bottom;

    			overlapB = overlapA;
    		}
    	}
    	if ((B.top > A.top) && (B.right > A.right) && (A.bottom > B.bottom))
    	{
    		overlapA = A;
    		overlapA.left = B.left;

    		overlapB = overlapA;
    	}


    		//transforming overlapA in terms of A = origin.
    		overlapA.left = overlapA.left - A.left;
    		overlapA.top = A.top - overlapA.top;
    		overlapA.right = overlapA.right - A.left;
    		overlapA.bottom = A.top - overlapA.bottom;

    		//transforming overlapB in terms of B = origin.
    		overlapB.left = overlapB.left - B.left;
    		overlapB.top = B.top - overlapB.top;
    		overlapB.right = overlapB.right - B.left;
    		overlapB.bottom = B.top - overlapB.bottom;


    	int xb = 0, yb = 0;
    	if (A.left == sCollision->boundingbox.left && A.right == sCollision->boundingbox.right && A.top == sCollision->boundingbox.top && A.bottom == sCollision->boundingbox.bottom)
    	{
    		yb = (int)overlapB.top;
    		xb = (int)overlapB.left;

    		for (int y = (int)overlapA.top; y < overlapA.bottom; y++)
    		{
    			for (int x = (int)overlapA.left; x < overlapA.right; x++)
    			{
    				if (sCollision->bitMask.bits[y*sCollision->bitMask.width + x] == true)
    				{
    					if (bitMask.bits[yb*bitMask.width + xb] == true)
    					{
    						std::cout << "Collision" << std::endl;
    						return true;
    					}
    					else
    						std::cout << "Failed" << std::endl;

    				}
    				xb++;
    			}
    			xb = (int)overlapB.left;
    			yb++;
    		}
    	}
    	else
    	{
    		yb = (int)overlapB.top;
    		xb = (int)overlapB.left;

    		for (int y = (int)overlapA.top; y < overlapA.bottom; y++)
    		{
    			for (int x = (int)overlapA.left; x < overlapA.right; x++)
    			{
    				if (bitMask.bits[y*bitMask.width + x] == true)
    				{
    					if (sCollision->bitMask.bits[yb*sCollision->bitMask.width + xb] == true)
    					{
    						std::cout << "Collision!" << std::endl;
    						return true;
    					}
    					else
    						std::cout << "Failed" << std::endl;
    				}
    				xb++;
    			}
    			xb = (int)overlapB.left;
    			yb++;
    			}
    		}

    */	return false;
}

std::stack<Collision *> *Collision::findCollision( int x_pos, int y_pos, Collision *self )
{
    using namespace ProcessManager;
    std::list<Collision *>::iterator checkIter, againstIter;
    std::stack<Collision *> *ret = NULL;

    /*checkIter = collisionList.begin();
    againstIter = collisionList.begin();
    againstIter++;

    for( checkIter = collisionList.begin(); checkIter != collisionList.end(); checkIter++ )
    	if( self != *checkIter && (*checkIter)->checkCollision( x_pos, y_pos ) )
    	{
    		if( !ret )
    			ret = new std::stack<Collision *>;

    		ret->push( *checkIter );
    	}

    return ret;*/
    return ret;
}
