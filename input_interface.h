/*
 *  SDL_input_interface.h
 *  Rad Adventure Development
 *
 */

#ifndef INPUT_INTERFACE_H
#define INPUT_INTERFACE_H

#include "InputHandler.h"

#ifdef _WIN32
#include "windows.h"
#else
#include <SDL/SDL.h>
#include <SDL/SDL_keysym.h>
#endif


namespace Input_Interface {
using namespace InputHandler;
#ifdef _WIN32
namespace Key_Codes {
/* Arrows */
const int RIGHT = VK_RIGHT;
const int LEFT = VK_LEFT;
const int DOWN = VK_DOWN;
const int UP = VK_UP;

/* Keypad */
const int KP_DIVIDE = VK_DIVIDE;
const int KP_MULTIPLY = VK_MULTIPLY;
const int KP_MINUS = VK_SUBTRACT;
const int KP_PLUS = VK_ADD;
const int KP_ENTER = VK_RETURN;
const int KP_1 = VK_NUMPAD1;
const int KP_2 = VK_NUMPAD2;
const int KP_3 = VK_NUMPAD3;
const int KP_4 = VK_NUMPAD4;
const int KP_5 = VK_NUMPAD5;
const int KP_6 = VK_NUMPAD6;
const int KP_7 = VK_NUMPAD7;
const int KP_8 = VK_NUMPAD8;
const int KP_9 = VK_NUMPAD9;
const int KP_0 = VK_NUMPAD0;
const int KP_PERIOD = VK_DECIMAL;

/* Misc */
const int HOME = VK_HOME;
const int PAGE_UP = VK_PRIOR;
const int PAGE_DOWN = VK_NEXT;
const int END = VK_END;
const int DELETE_KEY = VK_DELETE;
};

#else
#ifdef _SDL_H
namespace Key_Codes {
/* Arrows */
const int RIGHT = SDLK_RIGHT;
const int LEFT = SDLK_LEFT;
const int DOWN = SDLK_DOWN;
const int UP = SDLK_UP;

/* Keypad */
const int KP_DIVIDE = SDLK_KP_DIVIDE;
const int KP_MULTIPLY = SDLK_KP_MULTIPLY;
const int KP_MINUS = SDLK_KP_MINUS;
const int KP_PLUS = SDLK_KP_PLUS;
const int KP_ENTER = SDLK_KP_ENTER;
const int KP_1 = SDLK_KP1;
const int KP_2 = SDLK_KP2;
const int KP_3 = SDLK_KP3;
const int KP_4 = SDLK_KP4;
const int KP_5 = SDLK_KP5;
const int KP_6 = SDLK_KP6;
const int KP_7 = SDLK_KP7;
const int KP_8 = SDLK_KP8;
const int KP_9 = SDLK_KP9;
const int KP_0 = SDLK_KP0;
const int KP_PERIOD = SDLK_KP_PERIOD;

/* Misc */
const int HOME = SDLK_HOME;
const int PAGE_UP = SDLK_PAGEUP;
const int PAGE_DOWN = SDLK_PAGEDOWN;
const int DELETE = SDLK_DELETE;
const int END = SDLK_END;
};
#endif
#endif

void init();
void clean();


bool readInput( Input_Event * );
bool setTextMode(bool);

extern bool text_mode;

void AddInputToQueue(unsigned int, unsigned int, long);

};

namespace II = Input_Interface;

#endif
