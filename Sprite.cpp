/*
 *  Sprite.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof, Enda McNally, Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include "Sprite.h"
#include "graphics_engine.h"
#include <iostream>

Sprite::Sprite() {
    position.y = 0;
    position.x = 0;
    width = 0;
    rotation = 0;
    height = 0;

    visible = false;
}

Sprite::Sprite(std::wstring &bitmap_file ) {
    loadImage( bitmap_file );
}

Sprite::Sprite(float left, float top, float right, float bottom, GE::Image *image) {
    this->image = image;
    setSourceRect(left, top, right, bottom);

    width = source_rect.right - source_rect.left;
    height = source_rect.bottom - source_rect.top;
    visible = false;
    colour.v1.a, colour.v2.a, colour.v3.a, colour.v4.a = 255;
    colour.v1.r, colour.v2.r, colour.v3.r, colour.v4.r = 255;
    colour.v1.g, colour.v2.g, colour.v3.g, colour.v4.g = 255;
    colour.v1.b, colour.v2.b, colour.v3.b, colour.v4.b = 255;
    rotation = 0;
}

Sprite::~Sprite() {
    GE::unload(image);
}

std::ostream &operator<<(std::ostream &os, Sprite asprite) {
    os << "Top = " << asprite.source_rect.top
       << "\nLeft = " << asprite.source_rect.left
       << "\nBottom = " << asprite.source_rect.bottom
       << "\nRight = " << asprite.source_rect.right
       << "\nx = " << asprite.position.x << "\ny = " << asprite.position.y << std::endl << std::endl;

    return os;
}

Sprite &Sprite::operator=( Sprite const &arg ) {
    position.x = arg.position.x;
    position.y = arg.position.y;
    height = arg.height;
    width = arg.width;
    image = arg.image;

    return *this;
}

/*
 * Protected Methods
 */
void Sprite::setSourceRect(float left, float top, float right, float bottom) {
    source_rect.top = top / image->getHeight();
    source_rect.bottom = bottom / image->getHeight();
    source_rect.left = left / image->getWidth();
    source_rect.right = right / image->getWidth();
}

/*
 * Public Methods
 */
void Sprite::setScale(float scale) {
    width *= scale;
    height *= scale;
}

void Sprite::loadImage(std::wstring &bitmap_file) {
    image = GE::loadImageFromFile(&bitmap_file);
    setSize(image->getWidth(), image->getHeight());
    setSourceRect(0, 0, image->getWidth(), image->getHeight());
}

void Sprite::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

void Sprite::draw() {
    GE::drawSprite(this);
}

const Vector2 Sprite::center() {
    Vector2 temp;

    temp.x = position.x + width/2;
    temp.y = position.y - height/2;

    return temp;
}

float Sprite::getHeight() {
    return height;
}

float Sprite::getWidth() {
    return width;
}

/*
 * Static Functions
 */
void Sprite::DumpSprites(std::list<Sprite *> sprites) {
    std::list<Sprite *>::iterator iter;
    iter = sprites.begin();
    while (iter != sprites.end()) {
        std::cout << **iter;
        iter++;
    }
}

