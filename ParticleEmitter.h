/*
 *  ParticleEmitter.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H


#include "Particle.h"
#include "Timer.h"
#include "CRandom.h"
#include "Sprite.h"

#define SAFE_DELETE(p)	{if (p)	{ delete (p); (p) = NULL; } }

class Particle;

class ParticleEmitter : public Sprite {
public:
    ParticleEmitter();
    ~ParticleEmitter();

    Timer timer;

    void createParticle();
    virtual void draw();
    virtual void update();


    struct {
        float x, y;
    } pos;
    std::list<Particle *> particles;
    char* particleTexPntr;
    CRandom rand;

};
#endif
