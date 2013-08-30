/*
 *  Sprite.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof, Enda McNally, Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef SPRITE_H
#define SPRITE_H


#include <list>
#include <string>
#include "Image.h"
#include "Physics/Vector2.h"


class Sprite
{
public:
    Sprite();
    Sprite(std::wstring &);						/* Creates sprite with image file */
    Sprite(float left, float top,
           float right, float bottom, GE::Image*);	/* Use source rect supplied via arguments */
    ~Sprite();

    /* Location and dimension */
    Vector2 position;
    float width, height, layer;
    float rotation;

    bool visible;

    struct vert {
        int a, r, g, b;
    };
    struct {
        vert v1, v2, v3, v4;
    } colour;

    /* Location in image buffer to pull displayed image from.
     * Pretend they are protected for anywhere outside of Graphics_Engine
     */
    GE::Image *image;
    GE::Image::Rect source_rect;

    /* Accessor and getter functions */
    const Vector2 center();
    float getHeight();
    float getWidth();
    void setScale(float scale);
    void setWidth(float width);     /* Set width */
    void setSourceRect(float left, float top, float right, float bottom);
    inline void setSize(float w, float h) {
        width = w;
        height = h;
    };
    void setPosition(float, float);

    /* Image related */
    void draw();
    void loadImage(std::wstring &);

    /* Operator overloading functions */
    friend std::ostream &operator<<(std::ostream &os, Sprite asprite);
    Sprite &operator=( const Sprite & );

    /* Static functions */
    static std::list<Sprite *> LoadSpriteInfo( char * );
    static void DumpSprites(std::list<Sprite *> sprites);
};
#endif
