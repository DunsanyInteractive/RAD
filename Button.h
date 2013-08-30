/*
 *  Button.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef BUTTON_H
#define BUTTON_H
#define LEVEL_MEMBER_FUNCTION(funcPntr) ((Game::level)->*(funcPntr))


#include "Sprite.h"
#include "Animation.h"
#include "MouseInteractive.h"


// class Button : public MouseInteractive, public Animation, virtual public Sprite {
//
// public:
// 	Button();
// 	Button(std::wstringstream &fileStream, char* bitmap, std::wstring);
//
// 	void update();
// 	void operator++();
// 	void operator--();
//
//
// //	void checkCollisions(Sprite *);
//
// //	Collision *collision;
//
// 	/* Collidable interface */
// 	Vector2 center();
// 	float getHeight();
// 	float getWidth();
//
// 	protected:
// 		void createCollisionMask();
// };

#endif
