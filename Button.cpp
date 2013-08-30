/*
 *  Button.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof, Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include "Physics/Collision.h"
#include "Physics/CollisionManager.h"
#include "Game.h"
#include "Button.h"

// Button::Button()
// {
// 	createCollisionMask();
// }
//
//
// void Button::operator++()
// {
// 	if (frame < row_length && frame != frames)
// 	{
// 		sourceRect.left = sourceRect.right;
// 		sourceRect.right += (width / textureDimension);
// 		frame++;
// 	}
// 	else if ((frame == row_length) || (frame == frames))
// 	{
// 		if (frame == frames)
// 		{
//
// 		}
// 		else
// 		{
// 			row_length += length;
// 			sourceRect.right /= length;
// 			sourceRect.left = sourceRect.right - (width / textureDimension);
// 			sourceRect.top = sourceRect.bottom;
// 			sourceRect.bottom += (height / textureDimension);
// 			frame++;
// 		}
// 	}
//
// }
//
// void Button::operator--()
// {
// 	if ((frame <= row_length) && frame > (row_length - length + 1))
// 	{
// 		frame--;
// 		sourceRect.right = sourceRect.left;
// 		sourceRect.left -= (width / textureDimension);
//
// 	}
// 	else if ((frame == (row_length - length + 1)))
// 	{
// 		if (frame == frames)
// 		{
//
// 		}
// 		else
// 		{
// 			row_length -= length;
// 			sourceRect.right = (sourceRect.right * length);
// 			sourceRect.left = sourceRect.right - (width / textureDimension);
// 			sourceRect.bottom = sourceRect.top;
// 			sourceRect.top -= (height / textureDimension);
// 			frame--;
// 		}
// 	}
// }
//
//
// void Button::update()
// {
// 	Animation::update();
// 	Game::level->collision_manager->update( this );
// 	/*if( collision )
// 	{
// 		switch( collision->col_type )
// 		{
// 			case Collision::BUTTON_CLICK:
// 				if( ((MousePointer *)(collision->object))->isActive() )
// 					click();
// 				break;
// 			case Collision::MOUSE_OVER:
// 				++(*this);
// 				break;
// 			default:
// 				break;
// 		}
// 		collision->col_type = Collision::MISC;
// 	}*/
// }
//
// Vector2 Button::center()
// {
// 	return Sprite::center();
// }
//
// float Button::getHeight()
// {
// 	return height;
// }
//
// float Button::getWidth()
// {
// 	return width;
// }
//
// void Button::createCollisionMask()
// {
// 	mask = new CollisionMask( (int)getWidth(), (int)getHeight() );
// 	for( int i = 0; i < mask->size(); i++ )
// 		mask->mask[i] = true;
// }
