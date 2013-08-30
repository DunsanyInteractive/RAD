/*
 *  Guicon.cpp
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include "Guicon.h"
#include "../LuaEngine.h"

#ifndef _USE_OLD_IOSTREAMS

using namespace std;

#endif

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;
const char *LIB_NAME = "print";
#ifdef _DEBUG

void RedirectIOToConsole() {

    int hConHandle;
    long lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    FILE *fp;

    // allocate a console for this app
    AllocConsole();

    // set the screen buffer to be big enough to let us scroll text
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    coninfo.dwSize.Y = MAX_CONSOLE_LINES;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

    // redirect unbuffered STDOUT to the console
    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // redirect unbuffered STDIN to the console
    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "r" );
    *stdin = *fp;
    setvbuf( stdin, NULL, _IONBF, 0 );

    // redirect unbuffered STDERR to the console
    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stderr = *fp;
    setvbuf( stderr, NULL, _IONBF, 0 );

    // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
    // point to console as well
    ios::sync_with_stdio();
    luaopen_myprint(LuaEngine::state);
}

static int l_print(lua_State *L) {
    std::string output = lua_tostring(L, 1);
    std::cout <<  "LUA OUTPUT     :> " << output.c_str() << std::endl;
    return 0;
}

static const struct luaL_Reg winprint[] = {
    {"print", l_print},
    {NULL, NULL}
};

int luaopen_myprint(lua_State *L) {
    luaL_register(L,"winprint", winprint);
    luaL_dostring(L, "print = winprint.print");
    luaL_dostring(L, "print('Using windows print override for efficent output handeling!')");
    return 0;
}
#endif


//End of File
