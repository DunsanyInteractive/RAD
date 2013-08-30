/*
 *  Vector2.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
public:
    Vector2();
    Vector2(float X, float Y);
    ~Vector2();
    float x, y;

    //operator overloads using a single float as arguement
    void operator*(float arg);
    void operator+(float arg);
    void operator-(float arg);
    void operator*=(float arg);
    void operator+=(float arg);
    void operator-=(float arg);

    //operator overloads taking in another vector as an argument
    void operator*=(Vector2 arg);
    void operator+=(const Vector2 &arg);
    void operator-=(Vector2 arg);
    void operator*(Vector2 arg);
    void operator+(Vector2 arg);
    Vector2 operator-( const Vector2 &arg);
    void operator%(Vector2 arg);
    Vector2 operator=(const Vector2 arg);
    bool operator==(const Vector2 arg);

    //sets the x and y of the vector
    void setVector(float x, float y);

    float magnitude();
    float squareMagnitude();

    //Function to invert the Vectors to - and vice versa
    inline void invert();
    //Function to invert the x coordinate to - and vice versa
    inline void invert_x();
    //Function to invert the y coordinate to - and vice versa
    void invert_y();

    //Function that adds a Vector together and multiplies by a scale.
    void addScaledVector(Vector2 arg, float scale);
};
#endif
