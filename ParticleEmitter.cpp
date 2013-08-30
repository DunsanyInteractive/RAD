/*
 *
 *  ParticleEmitter.cpp
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */


// #include "graphics_engine.h"
// #include "ProcessManager.h"
// #include "ParticleEmitter.h"
//
// ParticleEmitter::ParticleEmitter()
// {
// 	pos.x = 0;
// 	pos.y = 0;
// 	std::wstring *filename = new std::wstring(L"Assets/Snowflakes.png");
// //	particleTexPntr = GE::loadImageFromFile(filename);
// 	SAFE_DELETE(filename);
// 	if (particleTexPntr == "ERROR")
// 	{
// 		throw (this);
// 	}
// 	ProcessManager::addProcess(this);
// 	rand.Randomize();
// 	layer = 4;
//
// }
//
// ParticleEmitter::~ParticleEmitter()
// {
//
// }
//
// //Creates a particle at a random location along the x coordinate and with a random lifespan
// void ParticleEmitter::createParticle()
// {
// 	float random = (float)rand.Random(20);
// 	random /= 10;
// 	random += 1.5;
// 	float xrand = ((float)rand.Random(1310) - 20);
// 	particles.push_back(new Particle(particleTexPntr, xrand, 50, random, rand));
// }
//
// //overloaded draw function. Makes sure Particles are all drawn together at the right time.
// void ParticleEmitter::draw()
// {
// 	std::list<Particle *>::iterator iter;
// 	iter = particles.begin();
// 	while (iter != particles.end())
// 	{
// 		GE::drawSprite(*iter);
// 		iter++;
// 	}
// }
//
// void ParticleEmitter::update()
// {
// 	float random = (float)rand.Random(2);
// 	random /= 10;
// 	if (timer.delay(random))
// 	{
// 		createParticle();
// 		createParticle();
// 	}
// 	//particles.remove_if(timer.flag1);
// 	std::list<Particle *>::iterator iter;
// 	iter = particles.begin();
// 	while (iter != particles.end())
// 	{
// 		if ((*iter)->selfDestruct)
// 		{
// 			delete(*iter);
// 			iter = particles.erase(iter);
// 		}
// 		(*iter)->update();
// 		iter++;
// 	}
// }
