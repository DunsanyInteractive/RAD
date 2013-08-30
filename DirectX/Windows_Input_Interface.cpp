/*
 *  Guicon.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#include "Windows_Input_Interface.h"
#include "windows.h"
#include "windowsx.h"
#include "../window_conf.h"

namespace Input_Interface {

using namespace Key_Codes;

bool text_mode = false;
std::queue<struct Input_Event *> event_queue;
bool chars;

unsigned int oemScan;
UINT vk;

void init() {

}

void clean()
{

}

bool setTextMode(bool TextMode)
{
    text_mode = TextMode;
    return text_mode;
}

bool readInput(Input_Event* ievent)
{
    if (event_queue.empty())
        return false;
    else
    {
        Input_Event* ptr_ievent;
        ptr_ievent = event_queue.front();
        *ievent =  *ptr_ievent;
        event_queue.pop();
        SAFE_DELETE(ptr_ievent);
        return true;
    }
}

void AddInputToQueue(UINT message, unsigned int wParam, long lParam)
{
    RECT cwin_size;
    GetClientRect( FindWindowEx(NULL, NULL, L"RAD",  L"Insert Game Name Here! Make sure to pull from LUA Script"), &cwin_size);
    Input_Event* inputevent;
    switch (message)
    {
    case WM_MOUSEMOVE:
        inputevent = new Input_Event;
        inputevent->type = MOUSE;
        inputevent->mouse.event_type = MOUSE_MOVEMENT;
        inputevent->mouse.x = (int)GET_X_LPARAM(lParam);
        inputevent->mouse.y = ((800 - (800 - cwin_size.bottom)) - (int)GET_Y_LPARAM(lParam)) ;
        event_queue.push(inputevent);
        break;

    case WM_LBUTTONDOWN:
        inputevent = new Input_Event;
        inputevent->type = InputHandler::MOUSE;
        inputevent->mouse.event_type = InputHandler::BUTTON_DOWN;
        inputevent->mouse.code = 1;
        inputevent->mouse.x = (int)GET_X_LPARAM(lParam);
        inputevent->mouse.y = 800 - (int)GET_Y_LPARAM(lParam);
        event_queue.push(inputevent);
        break;

    case WM_LBUTTONUP:
        inputevent = new Input_Event;
        inputevent->type = InputHandler::MOUSE;
        inputevent->mouse.event_type = InputHandler::BUTTON_UP;
        inputevent->mouse.code = 1;
        inputevent->mouse.x = (int)GET_X_LPARAM(lParam);
        inputevent->mouse.y = 800 - (int)GET_Y_LPARAM(lParam);
        event_queue.push(inputevent);
        break;

    case WM_RBUTTONDOWN:
        inputevent = new Input_Event;
        inputevent->type = InputHandler::MOUSE;
        inputevent->mouse.event_type = InputHandler::BUTTON_DOWN;
        inputevent->mouse.code = 2;
        inputevent->mouse.x = (int)GET_X_LPARAM(lParam);
        inputevent->mouse.y = 800 - (int)GET_Y_LPARAM(lParam);
        event_queue.push(inputevent);
        break;

    case WM_RBUTTONUP:
        inputevent = new Input_Event;
        inputevent->type = InputHandler::MOUSE;
        inputevent->mouse.event_type = InputHandler::BUTTON_UP;
        inputevent->mouse.code = 2;
        inputevent->mouse.x = (int)GET_X_LPARAM(lParam);
        inputevent->mouse.y = 800 - (int)GET_Y_LPARAM(lParam);
        event_queue.push(inputevent);
        break;

    case WM_MBUTTONDOWN:
        inputevent = new Input_Event;
        inputevent ->type = InputHandler::MOUSE;
        inputevent->mouse.event_type = InputHandler::BUTTON_DOWN;
        inputevent->mouse.code = 3;
        inputevent->mouse.x = (int)GET_X_LPARAM(lParam);
        inputevent->mouse.y = 800 - (int)GET_Y_LPARAM(lParam);
        event_queue.push(inputevent);
        break;

    case WM_MBUTTONUP:
        inputevent = new Input_Event;
        inputevent->type = InputHandler::MOUSE;
        inputevent->mouse.event_type = InputHandler::BUTTON_UP;
        inputevent->mouse.code = 3;
        inputevent->mouse.x = (int)GET_X_LPARAM(lParam);
        inputevent->mouse.y = 800 - (int)GET_Y_LPARAM(lParam);
        event_queue.push(inputevent);
        break;

        /*
        case WM_DEADCHAR:
        		if( DX_Input_Interface::text_mode )
        		{
        			inputevent->type = TEXT_ASCII;
        			InputHandler::bindKey( 96, &Console::enable );
        		}
        		else
        		{
        			inputevent->type = KEYBOARD;
        			InputHandler::bindKey( 96, &Console::disable );
        		}
        		inputevent->keyboard.key_pos = InputHandler::BUTTON_DOWN;
        		inputevent->keyboard.code = (int)wParam;
        		std::cout << "Key Down: " << wParam  << std::endl;
        		event_queue.push(inputevent);
        		break;
        */

    case WM_KEYDOWN:
        inputevent = new Input_Event;
        inputevent->keyboard.key_pos = InputHandler::BUTTON_DOWN;
        inputevent->type = KEYBOARD;
        oemScan = int(lParam & (0xff <<16)) >>16;
        vk = MapVirtualKey(oemScan, 1);

        switch(vk)
        {
            using namespace Key_Codes;
        case VK_PRIOR:
        case VK_NEXT:
        case VK_END:
        case VK_HOME:
        case VK_LEFT:
        case VK_UP:
        case VK_RIGHT:
        case VK_DOWN:
        case VK_SELECT:
        case VK_PRINT:
        case VK_EXECUTE:
        case VK_SNAPSHOT:
        case VK_INSERT:
        case VK_DELETE:
        case VK_HELP:
            /*	case KP_0:
            	case KP_1:
            	case KP_2:
            	case KP_3:
            	case KP_4:
            	case KP_5:
            	case KP_6:
            	case KP_7:
            	case KP_8:
            	case KP_9:
            	case KP_MULTIPLY:
            	case KP_PLUS:
            	case KP_MINUS:
            	case KP_PERIOD:
            	case KP_DIVIDE:
            */
        case VK_F1:
        case VK_F2:
        case VK_F3:
        case VK_F4:
        case VK_F5:
        case VK_F6:
        case VK_F7:
        case VK_F8:
        case VK_F9:
        case VK_F10:
        case VK_F11:
        case VK_F12:
        case VK_F13:
        case VK_F14:
        case VK_F15:
        case VK_F16:
        case VK_F17:
        case VK_F18:
        case VK_F19:
        case VK_F20:
        case VK_F21:
        case VK_F22:
        case VK_F23:
        case VK_F24:
        case VK_SHIFT:
        case VK_CONTROL:
            //		To get seperate Left and right control and shift will attempt
            //		ìmplementing GetAsyncKeyState() in the future
            //		case VK_RCONTROL:  186; break;
        case VK_CAPITAL:
            chars = false;
            break;

        default:
            chars = true;

            break;
        }
        inputevent->keyboard.code = vk;
        //				std::cout << "Key Up: " << inputevent->keyboard.code  << std::endl;

        if ((!chars)||(chars && !text_mode))
        {
            //					std::cout << "Key Up: " << inputevent->keyboard.code  << std::endl;
            event_queue.push(inputevent);
        }
        break;

    case WM_KEYUP:
        inputevent = new Input_Event;
        inputevent->keyboard.key_pos = InputHandler::BUTTON_UP;
        inputevent->type = KEYBOARD;
        oemScan = int(lParam & (0xff <<16)) >>16;
        vk = MapVirtualKey(oemScan, 1);

        switch(vk)
        {
            using namespace Key_Codes;
        case VK_PRIOR:
        case VK_NEXT:
        case VK_END:
        case VK_HOME:
        case VK_LEFT:
        case VK_UP:
        case VK_RIGHT:
        case VK_DOWN:
        case VK_SELECT:
        case VK_PRINT:
        case VK_EXECUTE:
        case VK_SNAPSHOT:
        case VK_INSERT:
        case VK_DELETE:
        case VK_HELP:
            /*	case KP_0:
            	case KP_1:
            	case KP_2:
            	case KP_3:
            	case KP_4:
            	case KP_5:
            	case KP_6:
            	case KP_7:
            	case KP_8:
            	case KP_9:
            	case KP_MULTIPLY:
            	case KP_PLUS:
            	case KP_MINUS:
            	case KP_PERIOD:
            	case KP_DIVIDE:
            */
        case VK_F1:
        case VK_F2:
        case VK_F3:
        case VK_F4:
        case VK_F5:
        case VK_F6:
        case VK_F7:
        case VK_F8:
        case VK_F9:
        case VK_F10:
        case VK_F11:
        case VK_F12:
        case VK_F13:
        case VK_F14:
        case VK_F15:
        case VK_F16:
        case VK_F17:
        case VK_F18:
        case VK_F19:
        case VK_F20:
        case VK_F21:
        case VK_F22:
        case VK_F23:
        case VK_F24:
        case VK_SHIFT:
        case VK_CONTROL:
            //		To get seperate Left and right control and shift will attempt
            //		ìmplementing GetAsyncKeyState() in the future
            //		case VK_RCONTROL:  186; break;
        case VK_CAPITAL:
            chars = false;
            break;

        default:
            chars = true;
//						std::cout << "Key Up: " << inputevent->keyboard.code  << std::endl;
            break;
        }
        inputevent->keyboard.code = vk;


        if ((!chars)||(chars && !text_mode))
        {
            //					std::cout << "Key Up: " << inputevent->keyboard.code  << std::endl;
            event_queue.push(inputevent);
        }
        break;


    case WM_CHAR:

        if(text_mode)
        {
            inputevent = new Input_Event;
            inputevent->keyboard.key_pos = InputHandler::BUTTON_DOWN;
            if( text_mode )
            {
                inputevent->type = TEXT_ASCII;
            }
            else
                inputevent->type = KEYBOARD;
            inputevent->keyboard.code = (int)wParam;
//						std::cout << "Button Pos : " << (lParam & (1 << (sizeof( LPARAM ) * 8 - 1))) << " Button : " << wParam  << std::endl;
            event_queue.push(inputevent);
            break;
        }
    }
}
};
