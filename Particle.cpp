/*
 *  Particle.cpp
 *  Rad Adventure Development
 *
 *  Created by _______________.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

// #include <math.h>
//
// #include "Particle.h"
//
// Particle::Particle()
// {
//
// }
//
// Particle::~Particle()
// {
//
// }
//
// Particle::Particle(char *texturePntr, float x, float y, double lifespan, CRandom r)
// {
// 	sourceRect.top = ((float)r.Random(4) * 64);
// 	sourceRect.left = ((float)r.Random(4) * 64);
// 	sourceRect.bottom = (sourceRect.top + 64);
// 	sourceRect.right = (sourceRect.left + 64);
// 	position.x = x;
// 	position.y = y;
// 	layer = 4;
// 	textureDimension = 256;
//
//
// 	width = sourceRect.right - sourceRect.left;
// 	height = sourceRect.bottom - sourceRect.top;
// 	visible = false;
// 	sourceRect.left /= textureDimension;
// 	sourceRect.top /= textureDimension;
// 	sourceRect.right /= textureDimension;
// 	sourceRect.bottom /= textureDimension;
// 	p_bitmap = texturePntr;
// 	bitmap_ID = (int)texturePntr;
//
// 	colour.v1.a = 255; colour.v2.a = 255; colour.v3.a = 255; colour.v4.a = 255;
// 	colour.v1.r = 255; colour.v2.r = 255; colour.v3.r = 255; colour.v4.r = 255;
// 	colour.v1.b = 255; colour.v2.g = 255; colour.v3.g = 255; colour.v4.g = 255;
// 	colour.v1.g = 255; colour.v2.b = 255; colour.v3.b = 255; colour.v4.b = 255;
// 	timer.dTimer.restart();
// 	lifeSpan = lifespan;
// 	selfDestruct = false;
//
// 	mass = 1.0f;
// 	inverseMass = (float)1/mass;
//
//
// 	acceleration.setVector(0.0f, -0.6f);
// 	velocity.setVector(0.0f, -4.0f);
// 	forceAccum.setVector(0.0f, 0.2f);
// 	damping = 0.85f;
//
// }
//
// //integrates and checks if it is time to destroy itself yet
// void Particle::update()
// {
//
// 	if (!timer.delay(lifeSpan))
// 	{
// 		float t = (float)timer.elapsed();
// 		integrate(t);
// 	}
// 	else
// 		selfDestruct = true;
// }
//
// //Integrates positional information to determine position based on velocity, mass, acceleration and force.
// void Particle::integrate(float duration)
// {
// 	if (duration < 2)
// 		duration += 1.0f;
//
// 	position.addScaledVector(velocity, duration);
//
// 	Vector2 resAcc = acceleration;
//
// 	resAcc.addScaledVector(forceAccum, inverseMass);
//
// 	velocity.addScaledVector(resAcc, duration);
//
// 	velocity *= powf(damping, duration);
//
// 	forceAccum.setVector(0, 0);
//
// }
