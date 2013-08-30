/*
 *  Only allows a single instance of a mouse pointer to exist
 */
#ifndef MOUSEPOINTER_H
#define MOUSEPOINTER_H

#include "Physics/Collidable.h"
#include "InputHandler.h"
#include "Sprite.h"

class Level;

class MousePointer : public Sprite {
private:
    void createCollisionMask();

    MousePointer(std::wstring file_name);
    ~MousePointer();

    bool clicked;
    static MousePointer* current_mouse;
public:
    typedef void (MousePointer::*funcPntr)(struct InputHandler::Mouse *);

    bool isClicked();

    void click();
    void unclick( void * );

    static MousePointer *load(std::wstring file_name);
    static void unload();
    static void updatePosition(InputHandler::Mouse *mouse);
};

#endif
