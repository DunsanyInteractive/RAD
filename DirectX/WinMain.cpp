/*
 *  WinMain.cpp
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett, Enda McNally.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#include <Windows.h>
#include <Windowsx.h>
#include <iostream>
#include <windef.h>

#include "../input_interface.h"
#include "../window_conf.h"
#include "guicon.h"
#include "DX_Engine.h"
#include "../Font_Handler.h"
#include "../InputHandler.h"
#include "../Console.h"
#include "../Game.h"
#include "../SoundManager.h"
#include "../LuaEngine.h"

GUID *pguid;	//The user interface

#define CALL_MEMBER_FUNCTION(funcPntr) ((Game::mousePointer)->*(funcPntr))

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    HWND hWnd;
    WNDCLASSEX wc;
    bool CurrWin = true;
    ZeroMemory( &wc, sizeof(WNDCLASSEX));

    std::string target = lpCmdLine;

    /* Directory */
    std::wstring dir(target.size(), L'');
    size_t pos = target.find_last_of('\\');
    copy(target.begin(), target.begin() + pos, dir.begin());

    /* File */
    std::string file = target.substr(pos + 1);

    /*Temp Label for the window until a LUA script can be used to get name from*/
    LPCWSTR game_name = L"Insert Game Name Here! Make sure to pull from LUA Script";

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"RAD";


    II::init();

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(	NULL,
                            L"RAD",
                            game_name,
                            //						WS_EX_TOPMOST|WS_POPUP,     /*Full screen Setting*/
                            WS_OVERLAPPEDWINDOW,
                            100,
                            78,
                            WINDOW_WIDTH,
                            WINDOW_HEIGHT,
                            NULL,
                            NULL,
                            hInstance,
                            NULL);

    ShowWindow(hWnd, nShowCmd);
    MSG msg;
    ZeroMemory( &msg, sizeof(msg));

    CoInitialize( NULL );
    InputHandler::bindKey( 223, &Console::enable );

    try {
        GE::initialize(hWnd, hInstance);
    }
    catch(HRESULT e)
    {
        std::cerr << "Failed to Initialize program with error code: " <<  e << std::endl;
        system("exit");
    }

    Game::initialize();
    ::SetCurrentDirectory(dir.c_str());

#ifdef _DEBUG
    RedirectIOToConsole();
#endif
    LuaEngine::run("LoadLevel('" + file + "')");
    DWORD starting_point = GetTickCount();
    HKL English = LoadKeyboardLayout(L"00000809", KLF_ACTIVATE);

    /* Game Loop starts */
    while(Game::appRunning)
    {
        starting_point = GetTickCount();

        while (PeekMessageW(&msg, hWnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Game::update();
        Game::display();
        while((GetTickCount() - starting_point) < 15);
    }

    //Game Loop ends
    Game::clean();
    return msg.wParam;
}



LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    bool active;
    HWND pWndOther;


    switch(message)
    {


    case WM_CLOSE:
    {
        // display message box
        int result =  MessageBoxW(hWnd,	L"Are you sure you want to quit?", L"RAD", MB_YESNO | MB_ICONQUESTION);

        // does the user want to close?
        if (result == IDYES)
        {
            // call default handler
            Game::exit();
            return (DefWindowProc(hWnd, message, wParam, lParam));
        } // end if
        else // throw message away
            return(0);

    }
    break;


    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        break;

    case WM_QUIT:
        PostQuitMessage(0);
        return 0;
        break;

    case WM_ACTIVATE:
        active = wParam != WA_INACTIVE;
        pWndOther = (HWND)lParam;
        if (active)
        {
            SM::sound->play();

        }

        else
        {
            SM::sound->pause();
        }
        break;

    default:
        II::AddInputToQueue(message,  wParam,  lParam);
        break;

    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
