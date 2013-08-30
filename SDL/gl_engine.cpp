/*
 *  gl_engine.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include <cmath>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include "GL/glu.h"
#include <iostream>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "window.h"
#include "../Game.h"
#include "../window_conf.h"
#include "../graphics_engine.h"
#include "../window_conf.h"
#include "../Physics/Vector2.h"

namespace Graphics_Engine {
int layer;

/* Cache of loaded images */
std::map<std::wstring, Image*>	loaded_bitmaps;

/* Used for storing image properties */
struct Record {
    Record(int num, std::wstring file_name, bool* mask) {
        this->num = num;
        this->file_name = file_name;
        this->mask = mask;
    }
    ~Record() {
        if (mask) delete mask;
    }
    unsigned int num;		/* Number of references to image */
    std::wstring file_name;	/* File name assoicated with image */
    bool* mask;				/* Contact mask */
};
struct std::map<Image*, Record*> properties;

void init() {
    /* Initialize window */
    SDL::init();

    /* Make the viewport cover the whole window */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D( 0, WINDOW_WIDTH, 0, WINDOW_HEIGHT );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* set the clear color to white */
    glClearColor( 0, 0, 0, 0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable( GL_BLEND );
    glEnable( GL_ALPHA_TEST );	/* Enable alpha testing */
    glEnable( GL_DEPTH_TEST );	/* We want z-buffer tests enabled*/
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_REPLACE );			/* Textures: Replace dest pixel with source pixel */
    glShadeModel( GL_SMOOTH );

    /* Blending */
    glEnable( GL_BLEND );
    glEnable( GL_ALPHA_TEST );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    /* Do not draw back-facing polygons*/
    glEnable(GL_CULL_FACE);
    glCullFace( GL_BACK );

    /* Default level is the Menu */
    layer = 0;
}

void clean() {
    std::map<std::wstring, Image*>::iterator it;
    for (it = loaded_bitmaps.begin(); it != loaded_bitmaps.end(); it++) {
        Image *image = it->second;
        glDeleteTextures(1, &(image->id.i));
        delete it->second;
    }

    /* Delete stored properties */
    std::map<Image*, Record*>::iterator it2;
    for (it2 = properties.begin(); it2 != properties.end(); it2++)
        delete it->second;
}

void display() {
    Game::draw();
    SDL_GL_SwapBuffers();
    glClear( GL_DEPTH_BUFFER_BIT );
}

void drawLine( float x, float y, float x_end, float y_end ) {
    glLineWidth( 0.1 );
    glColor4f( 0, 1, 0, 1 );
    glBindTexture( GL_TEXTURE_2D, 0 );
    glBegin( GL_LINE_STRIP );
    glVertex3f( x, y, 0.98 );
    glVertex3f( x_end, y_end, 0.98 );
    glEnd();
    glColor4f( 1, 1, 1, 1 );
}

void drawCircle( float x, float y, float radius, float r, float g, float b ) {
    const float PI = 3.14159265;

    glLineWidth( 0.1 );
    glColor4f( r, g, b, 1 );
    glBindTexture( GL_TEXTURE_2D, 0 );
    glBegin( GL_LINE_LOOP );
    for( int i = 0; i < 360; i++ )
        glVertex3f( x + radius*sin( i*PI/180 ), y + radius*cos( i*PI/180 ), 0.98 );
    glEnd();
    glColor4f( 1, 1, 1, 1 );
}

void drawSprite( Sprite *sprite ) {
    GE::useLayer( sprite->layer  );
#define TOP_Y	sprite->position.y
#define BOT_Y	(sprite->position.y - sprite->height)
#define LEFT_X	sprite->position.x
#define	RIGHT_X	(sprite->position.x + sprite->width)

    glBindTexture( GL_TEXTURE_2D, sprite->image->id.i );
    glBegin( GL_QUADS );
    glTexCoord2f( sprite->source_rect.left, sprite->source_rect.top );
    glVertex3f( LEFT_X, TOP_Y, 0 );
    glTexCoord2f( sprite->source_rect.left, sprite->source_rect.bottom );
    glVertex3f( LEFT_X, BOT_Y, 0 );
    glTexCoord2f( sprite->source_rect.right, sprite->source_rect.bottom );
    glVertex3f( RIGHT_X, BOT_Y, 0 );
    glTexCoord2f( sprite->source_rect.right, sprite->source_rect.top );
    glVertex3f( RIGHT_X, TOP_Y, 0 );
    glEnd();
}

bool *createBitmask( Image *image ) {
    std::map<Image*, Record*>::iterator it = properties.find(image);
    if (it == properties.end()) {
        //TODO: Throw error
        std::cout << __FILE__;
        std::cout << __LINE__;
        std::cout << (" Image was not loaded");
        std::cout << std::endl;
        return NULL;
    } else
        return it->second->mask;
}

const int supportedLayers() {
    return 1 / LAYER_DIFF;
}

void useLayer( int arg ) {
    glLoadIdentity();
    glTranslatef( 0, 0, arg * -LAYER_DIFF );
}

/* 32-bit RGBA format */
SDL_PixelFormat pixel_format = {
    NULL,
    32,			/* BitsPerPixel */
    4,			/* BytesPerPixel */
    NULL,		/* Rloss */
    NULL,		/* Bloss */
    NULL,		/* Gloss */
    NULL,		/* Aloss */
    NULL,		/* Rshift */
    NULL,		/* Bshift */
    NULL,		/* Gshift */
    NULL,		/* Ashift */
    0x000000ff,		/* Rmask */
    0x0000ff00,		/* Bmask */
    0x00ff0000,		/* Gmask */
    0xff000000,		/* Amask */
};

/* Used for contact resolution */
bool* createContactMask( SDL_Surface *surf ) {
    bool	*contact;
    Uint32	*p;
    Uint32	alpha_mask;
    int			size;

    size = surf->h * surf->w;
    if (size <= 0) {
        std::cout << __FILE__;
        std::cout << __LINE__;
        std::cout << ("Fatal Error: Could not create contact mask");
        std::cout << std::endl;
        exit(-1);
    }

    p = (Uint32 *)surf->pixels;
    alpha_mask = surf->format->Amask;
    contact = new bool[size];
    for( int i = 0; i < size; i++ )
        contact[i] = ( p[i] && alpha_mask ) ? true : false;

    return contact;
}

Image *loadImageFromFile( std::wstring *arg ) {
    std::map<std::wstring, Image*>::iterator	iter;
    Image *ret;

    /* Already loaded, return from cache and increment count */
    iter = loaded_bitmaps.find(*arg);
    if (iter != loaded_bitmaps.end()) {
        ret = iter->second;
        properties[ret]->num++;
        return ret;
    }

    int bitmap_ID;
    std::string temp( arg->length(), ' ' ); /* Will only work if wstring is using standard encoding, should be fixed */

    copy(arg->begin(), arg->end(), temp.begin());
    SDL_Surface *surf = IMG_Load( temp.c_str() );
    if (!surf) {
        std::cout << "Could not load image file: " << temp.c_str() << std::endl;
        return NULL;
    } else
        std::cout << "Loaded image: " << temp.c_str() << std::endl;


    /* Convert surface */
    {
        SDL_Surface *temp_surf;
        temp_surf = SDL_ConvertSurface( surf, &pixel_format, 0 );
        SDL_FreeSurface( surf );
        surf = temp_surf;
        if (!surf) {
            std::cout << "Could not convert image file: " << temp.c_str() << std::endl;
            //TODO: Throw error
            return NULL;
        }
    }

    /* Load texture */
    glGenTextures( 1, (GLuint*)&bitmap_ID );
    glBindTexture( GL_TEXTURE_2D, bitmap_ID );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    /* Create new local image type for return */
    ret = new Image(bitmap_ID, surf->w, surf->h);

    /* Save record of image */
    //TODO: We should not need to save this for every image
    properties[ret] = new Record(
        1,
        *arg,				/* File Name */
        createContactMask(surf)
    );

    /* Create local image type and free loaded image */
    SDL_FreeSurface(surf);

    loaded_bitmaps[ *arg ] = ret;
    return ret;
}

/* Registers a removal of an instance of an object using an image.
 * Deletes it if necessary */
void unload(Image *image) {
    /* Find record */
    std::map<Image*, Record*>::iterator iter;
    iter = properties.find(image);
    if (iter == properties.end()) {
        /* Error */
        std::cout << __FILE__;
        std::cout << __LINE__;
        std::cout << (" Error: File not already loaded");
        std::cout << std::endl;
        return;
    }

    /* Modify */
    Record *record = iter->second;
    if (record->num > 1)
        record->num--;
    else {
        /* Delete record if last one */
        Image *image = loaded_bitmaps.find(record->file_name)->second;
        glDeleteTextures(1, &(image->id.i));
        properties.erase(iter);
        delete image;
        delete record;
    }
}
};
