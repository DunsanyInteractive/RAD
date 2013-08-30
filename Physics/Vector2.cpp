/*
 *  Vector2.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#include <cmath>

#include "Vector2.h"

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float X, float Y) : x(X), y(Y) {}

Vector2::~Vector2() {}

void Vector2::operator*(float arg)		{
    x *= arg;
    y *= arg;
}

void Vector2::operator+(float arg)		{
    x += arg;
    y += arg;
}

void Vector2::operator-(float arg)		{
    x -= arg;
    y -= arg;
}

void Vector2::operator*=(float arg)	{
    x *= arg;
    y *= arg;
}

void Vector2::operator*(Vector2 arg)	{
    x *= arg.x;
    y *= arg.y;
}

void Vector2::operator+(Vector2 arg)	{
    x += arg.x;
    y += arg.y;
}

Vector2 Vector2::operator-( const Vector2 &arg)
{
    return Vector2( x - arg.x, y - arg.y );
}

void Vector2::operator+=( const Vector2 &arg ) {
    x += arg.x;
    y += arg.y;
}

bool Vector2::operator==(const Vector2 arg)		{
    if (x == arg.x && y == arg.y) return true;
    else return false;
}

Vector2 Vector2::operator=(const Vector2 arg)	{
    x = arg.x;
    y = arg.y;
    return *this;
}

void Vector2::operator%(Vector2 arg)	{
    y*=arg.x;
    x*=arg.y;
}

void Vector2::setVector(float X, float Y) {
    x = X;
    y = Y;
}

float Vector2::magnitude()
{
    return sqrt( this->squareMagnitude() );
}

float Vector2::squareMagnitude()
{
    return x * x + y * y;
}

inline void Vector2::invert() {
    x = -x;
    y = -y;
}

inline void Vector2::invert_x()	{
    x = -x;
}

void Vector2::invert_y()	{
    y = -y;
}

void Vector2::addScaledVector(Vector2 arg, float scale)
{
    x += arg.x * scale;
    y += arg.y * scale;
}
