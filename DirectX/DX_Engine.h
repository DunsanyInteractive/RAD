/*
 *  DX_Engine.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef DXENGINE_H
#define DXENGINE_H

#include <d3d9.h>
#include <d3dx9core.h>
#include "../graphics_engine.h"
#include "../Sprite.h"

#define CLIENT_WIDTH 1264
#define CLIENT_HEIGHT 762


namespace Graphics_Engine {
/* Variables */
/* Direct X */
extern LPDIRECT3D9 pd3d;
extern LPDIRECT3DDEVICE9 pd3ddev;
extern std::list<IDirect3DTexture9*> m_gfxSet;
extern IDirect3DVertexBuffer9* vertexBatchBuffer;
extern IDirect3DIndexBuffer9* indexBatchBuffer;
extern IDirect3DSurface9* backbuffer;
extern IDirect3DVertexBuffer9* vertexBuffer;


extern LPD3DXEFFECT colourModulator;
extern D3DXHANDLE shaderTechnique;
extern LPD3DXBUFFER errorLog;

extern int drawLayer, numBatchVerts;
extern float batchTexHeight, batchTexWidth;
extern D3DXMATRIX matOrtho;
extern D3DXMATRIX matIdentity;

const DWORD D3DFVF_TLVERTEX = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
const int BATCH_BUFFER_SIZE = 120;

struct TLVERTEX {
    float x;
    float y;
    float z;
    //	float rhw;
    D3DCOLOR colour;
    float u;
    float v;
};
extern TLVERTEX* batchVertices;
extern TLVERTEX* vertices;
/* Functions */
/* Direct X */
/* Init related functions*/
void initialize(HWND hWnd, HINSTANCE hInst);

void clearTextureList();
DWORD grabTickCount();

//Batch draw Functions
void beginBatchDrawing(IDirect3DTexture9*, Sprite *sprite);
void endBatchDrawing();
void addQuad(Sprite *);
void FillIndexBuffer();

extern bool batchDrawingStarted;

/* Graphic related functions */
};

#endif
