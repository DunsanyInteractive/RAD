/*
 *  DX_Engine.cpp
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett
 *  Copyright 2011 Dunsany Interactive. All rights reserved.
 *
 */
#include "../window_conf.h"
#include "DX_Engine.h"
#include "windows.h"
#include "../Game.h"
#include <iostream>
#include <map>

/* Instantiation of variables */
/* Direct X */
namespace Graphics_Engine {
LPDIRECT3D9 pd3d;
LPDIRECT3DDEVICE9 pd3ddev;
std::map<std::wstring, Image*> loadedTextures;
int drawLayer; /*current layer to draw on*/
bool batchDrawingStarted; /*Flag to tell if in middle of drawing*/
char* currentTexture;	/*current Texture that has been set for drawing*/

LPD3DXEFFECT colourModulator;
D3DXHANDLE shaderTechnique;
LPD3DXBUFFER errorLog;

/*Seperate Sprite Implementation*/
IDirect3DVertexBuffer9* vertexBuffer;
IDirect3DVertexBuffer9* vertexBatchBuffer;
IDirect3DIndexBuffer9* indexBatchBuffer;
int numBatchVerts;
IDirect3DSurface9* backbuffer;
TLVERTEX* batchVertices;
float batchTexHeight, batchTexWidth;
D3DXMATRIX matOrtho;
D3DXMATRIX matIdentity;
TLVERTEX* vertices;

/* Struct to store all the properties for the image */
struct Record {
    Record(std::wstring file_name, bool* col_mask) {
        num_ref = 1;
        fileName = file_name;
        mask = col_mask;
    }
    void setMask(bool* col_mask) {
        mask = col_mask;
    }
    ~Record() {
        SAFE_DELETE(mask);    /*destructor for the mask pointer*/
    }
    unsigned int num_ref; /*number of file references to image file*/
    std::wstring fileName; /*Filename of the image in use*/
    bool* mask; /*pointer to the collision mask for the image*/
};

/*Map that will store information about the images in use*/
std::map<Image*, Record*> properties;

/*Destructor*/
void clean() {
    if (pd3d != NULL) {
        HRESULT hr = pd3d->Release();
        if (FAILED(hr))
            std::cerr << "ERROR! Cant release pd3d!" << std::endl;
    }
    if (pd3ddev != NULL) {
        HRESULT hr = pd3ddev->Release();
        if (FAILED(hr))
            std::cerr << "ERROR! Cant release pd3ddev!" << std::endl;
    }

    pd3ddev->SetStreamSource(0, NULL, 0, 0);
    if (vertexBuffer != NULL)
        vertexBuffer->Release();
    if (vertexBatchBuffer != NULL)
        vertexBatchBuffer->Release();
    if (indexBatchBuffer != NULL)
        indexBatchBuffer->Release();
    colourModulator->Release();
}

/*Directx Inititalisation Function*/
/*Creates Devices and prepares Program for a Directx environment.*/
void initialize(HWND hWnd, HINSTANCE hInst) {
    pd3d = NULL;
    pd3ddev = NULL;

    /*Initialize devices*/
    pd3d = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));


    /*Code to find out size of client area of window*/
    RECT win_client_size;
    GetClientRect(hWnd, &win_client_size);

    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = CLIENT_WIDTH;		/*win_client_size.right;*/
    d3dpp.BackBufferHeight = CLIENT_HEIGHT;		/*win_client_size.bottom;*/
    d3dpp.hDeviceWindow = hWnd;

    d3dpp.EnableAutoDepthStencil = true;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    HRESULT hr = pd3d->CreateDevice(D3DADAPTER_DEFAULT,
                                    D3DDEVTYPE_HAL,
                                    hWnd,
                                    D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                    &d3dpp,
                                    &pd3ddev);
    if (FAILED(hr))	{
        std::cerr << "ERROR! Failed to initialize a Direct3D Device" << std::endl;
        throw(hr);
    }
    /*Set Vertex Format*/
    pd3ddev->SetFVF(D3DFVF_TLVERTEX);

    /*Create the vertex buffer*/
    pd3ddev->CreateVertexBuffer(sizeof(TLVERTEX) * 4, NULL, D3DFVF_TLVERTEX, D3DPOOL_MANAGED, &vertexBuffer, NULL);
    pd3ddev->CreateVertexBuffer(BATCH_BUFFER_SIZE * sizeof(TLVERTEX), D3DUSAGE_WRITEONLY, D3DFVF_TLVERTEX, D3DPOOL_MANAGED, &vertexBatchBuffer, NULL);
    pd3ddev->CreateIndexBuffer(BATCH_BUFFER_SIZE * 3, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBatchBuffer, NULL);
    pd3ddev->SetIndices(indexBatchBuffer);
    numBatchVerts = 0;

    /*Set render and texture stage state*/
    pd3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    pd3ddev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    pd3ddev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    pd3ddev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

    pd3ddev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    pd3ddev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    pd3ddev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);

    pd3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pd3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    pd3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

    /*set up orthographic projection matrix*/
    D3DXMatrixOrthoLH(&matOrtho, CLIENT_WIDTH, CLIENT_HEIGHT, 1.0f, 10.0f);
    D3DXMatrixIdentity(&matIdentity);

    /*Load the shader File*/
    D3DXCreateEffectFromFile(pd3ddev, L"Fx/ColourModulation.fx", 0, 0,  D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY, 0, &colourModulator, &errorLog);
    colourModulator->FindNextValidTechnique(NULL, &shaderTechnique);

    /*fill index buffer*/
    FillIndexBuffer();
    batchDrawingStarted = false;
}

/*DirectX Display Function*/
void display() {
    /*clear the backbuffer and set the colour to black*/
    pd3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
    /*initialize drawing sequence*/
    pd3ddev->BeginScene();
    /*initialise the shader called colour modulator*/
    colourModulator->Begin(NULL, NULL);
    /*draw the entire level*/
    Game::level->drawLevel();
    /*ends draw sequence*/
    colourModulator->End();
    pd3ddev->EndScene();
    pd3ddev->Present(NULL, NULL, NULL, NULL);		/*Displays the backbuffer to the screen*/
}

void drawSprite(Sprite *sprite) {
    D3DXMATRIX matObj, matRot, matFinal, matTrans;
    pd3ddev->SetFVF(D3DFVF_TLVERTEX);
    D3DXMatrixIdentity(&matObj);
    float X, Y, destWidth, destHeight;

    /*Calculate Coordinates*/
    X = sprite->position.x - ((float)(CLIENT_WIDTH) / 2);
    Y = sprite->position.y - ((float)(CLIENT_HEIGHT) / 2);
    destWidth = (float)sprite->width;
    destHeight = (float)sprite->height;

    /*set coordinates of 4 vertices for our quad*/
    TLVERTEX verts[] = {
        { X, Y, sprite->layer, D3DCOLOR_ARGB(sprite->colour.v1.a, sprite->colour.v1.r, sprite->colour.v1.g, sprite->colour.v1.b), sprite->source_rect.left, sprite->source_rect.top,},
        { (X + destWidth), Y, sprite->layer, D3DCOLOR_ARGB(sprite->colour.v2.a, sprite->colour.v2.r, sprite->colour.v2.g, sprite->colour.v2.b), sprite->source_rect.right, sprite->source_rect.top,},
        {  (X + destWidth), (Y - destHeight), sprite->layer, D3DCOLOR_ARGB(sprite->colour.v3.a, sprite->colour.v3.r, sprite->colour.v3.g, sprite->colour.v3.b), sprite->source_rect.right, sprite->source_rect.bottom,},
        {  X, (Y - destHeight), sprite->layer, D3DCOLOR_ARGB(sprite->colour.v4.a, sprite->colour.v4.r, sprite->colour.v4.g, sprite->colour.v4.b), sprite->source_rect.left, sprite->source_rect.bottom,},
    };

    /*Setup vertices in buffer*/
    VOID* pVoid;
    vertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, verts, sizeof(verts));
    vertexBuffer->Unlock();

    if (sprite->rotation) {
        D3DXMatrixTranslation(&matTrans,(-X) - sprite->width/2, (-Y) + sprite->height/2, 1.0f);
        D3DXMatrixRotationZ(&matRot, sprite->rotation);
        D3DXMatrixMultiply(&matFinal, &matTrans, &matRot);
        D3DXMatrixTranslation(&matTrans, (((X)+ sprite->width/2)), (((Y - sprite->height/2))), 1.0f);
        D3DXMatrixMultiply(&matFinal, &matFinal, &matTrans);
        colourModulator->SetMatrix("World", &matFinal);
    } else
        colourModulator->SetMatrix("World", &matObj);

    colourModulator->SetMatrix("View", &matOrtho);
    colourModulator->CommitChanges();
    pd3ddev->SetStreamSource(0, vertexBuffer, 0, sizeof(TLVERTEX));
    pd3ddev->SetTexture(0, (IDirect3DTexture9*)sprite->image->id.p);
    colourModulator->BeginPass(0);

    /*draw quads in the buffer*/
    pd3ddev->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
    colourModulator->EndPass();


}

/*returns the supported layers of the engine*/
const int supportedLayers() {
    return 11;
}

/*sets the drawing layer to the argument*/
void useLayer(int arg) {
    try {
        if (arg < drawLayer)
            throw arg;
        else
            drawLayer = arg;
    }
    catch (int arg) {
        std::cerr << "Can not draw to a a lower z-axis after a higher z-axis layer is drawn. " << arg << " is lower then " << drawLayer << std::endl;
    }
}

/*Loads asset to Surface Object*/
Image* loadImageFromFile(std::wstring* filename) {
    try {
        /*declare iterator to find record in map*/
        std::map<std::wstring, Image*>::iterator iter;
        iter = loadedTextures.find(*filename);
        if (iter != loadedTextures.end()) {
            Image* img = loadedTextures[*filename];
            properties[img]->num_ref++;
            return img;
        } else {
            D3DXIMAGE_INFO imageInfo;																												//creates an Object that takes in the image information from the jpg
            HRESULT hr = D3DXGetImageInfoFromFile(filename->c_str(), &imageInfo);																			//Loads that info to the Object
            if (FAILED(hr)) {
                std::wcerr << "ERROR! Failed to get bitmap info from the source image file... " << filename->c_str() << std::endl;
                throw (hr);
            }
            /*create temp texture and load the image into memory*/
            IDirect3DTexture9* tempTexture;
            hr = D3DXCreateTextureFromFileEx(pd3ddev, filename->c_str(), 0, 0, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_BOX, D3DX_DEFAULT, 0, &imageInfo, NULL, &tempTexture) ;	//Loads the image to that surface
            if (FAILED(hr)) {
                std::cerr << "Failed to load texture: " << filename << " ERROR: " << __FILE__ << " at Line " << __LINE__ << std::endl;
                throw(hr);
            }
            /*Add texture to loadedTextures and set the Record*/
            Image* image = new Image((char*)tempTexture, imageInfo.Width, imageInfo.Height);
            loadedTextures[*filename] = image;
            properties[image] = new Record(*filename, NULL);

            /*return the new Image*/
            return loadedTextures[*filename];
        }
    } catch (HRESULT hr) {
        std::cerr << "ERROR CODE: " << hr << std::endl;
        return NULL;
    }
}

/*Fill Index Buffer*/
void FillIndexBuffer() {
    int index = 0;
    short* indices = NULL;

    /*lock index Buffer*/
    indexBatchBuffer->Lock(0, BATCH_BUFFER_SIZE * 3, (void**) &indices, 0);

    for (int vertex = 0; vertex < BATCH_BUFFER_SIZE; vertex +=4) {
        indices[index] = vertex;
        indices[index + 1] = vertex + 2;
        indices[index + 2] = vertex + 3;
        indices[index + 3] = vertex;
        indices[index + 4] = vertex + 1;
        indices[index + 5] = vertex + 2;
        index += 6;
    }

    /*Unlock index buffer*/
    indexBatchBuffer->Unlock();
}

void beginBatchDrawing(IDirect3DTexture9* texture, Sprite *sprite) {
    D3DXMATRIX matIdentity;
    D3DSURFACE_DESC surfDesc;

    /*lock the batching vertexBuffer*/
    numBatchVerts = 0;
    vertexBatchBuffer->Lock(0, BATCH_BUFFER_SIZE * sizeof(TLVERTEX), (void**) &batchVertices, 0);

    /*Gettexture dimensions*/
    texture->GetLevelDesc(0, &surfDesc);
    batchTexWidth = (float) surfDesc.Width;
    batchTexHeight = (float) surfDesc.Height;

    /*Set Texture*/
    pd3ddev->SetTexture(0, texture);
    pd3ddev->SetFVF(D3DFVF_TLVERTEX);
    D3DXMATRIX matRotate;
    D3DXMATRIX matWorld;
    D3DXMatrixIdentity(&matWorld);

    /*Set world translation matrix*/
    D3DXMatrixIdentity(&matIdentity);
    colourModulator->SetMatrix("View", &matOrtho);
    colourModulator->SetMatrix("World", &matIdentity);

    colourModulator->CommitChanges();

    /*Set stream source to batch buffer*/
    pd3ddev->SetStreamSource(0, vertexBatchBuffer, 0, sizeof(TLVERTEX));

    batchDrawingStarted = true;
}

void addQuad(Sprite *sprite) {
    float X, Y, destWidth, destHeight;

    /*Calculate Coordinates*/
    X = sprite->position.x - ((float)(CLIENT_WIDTH) / 2);
    Y = sprite->position.y - ((float)(CLIENT_HEIGHT) / 2);
    destWidth = (float)sprite->width;
    destHeight = (float)sprite->height;

    /*Setup vertices in buffer*/
    batchVertices[numBatchVerts].colour = D3DCOLOR_ARGB(sprite->colour.v1.a, sprite->colour.v1.r, sprite->colour.v1.g, sprite->colour.v1.b);
    batchVertices[numBatchVerts].x = X;
    batchVertices[numBatchVerts].y = Y;
    batchVertices[numBatchVerts].z = sprite->layer;
    batchVertices[numBatchVerts].u = sprite->source_rect.left;
    batchVertices[numBatchVerts].v = sprite->source_rect.top;

    batchVertices[numBatchVerts + 1].colour = D3DCOLOR_ARGB(sprite->colour.v2.a, sprite->colour.v2.r, sprite->colour.v2.g, sprite->colour.v2.b);
    batchVertices[numBatchVerts + 1].x = X + destWidth;
    batchVertices[numBatchVerts + 1].y = Y;
    batchVertices[numBatchVerts + 1].z = sprite->layer;
    batchVertices[numBatchVerts + 1].u = sprite->source_rect.right;
    batchVertices[numBatchVerts + 1].v = sprite->source_rect.top;

    batchVertices[numBatchVerts + 2].colour = D3DCOLOR_ARGB(sprite->colour.v3.a, sprite->colour.v3.r, sprite->colour.v3.g, sprite->colour.v3.b);
    batchVertices[numBatchVerts + 2].x = X + destWidth;
    batchVertices[numBatchVerts + 2].y = Y - destHeight;
    batchVertices[numBatchVerts + 2].z = sprite->layer;
    batchVertices[numBatchVerts + 2].u = sprite->source_rect.right;
    batchVertices[numBatchVerts + 2].v = sprite->source_rect.bottom;

    batchVertices[numBatchVerts + 3].colour = D3DCOLOR_ARGB(sprite->colour.v4.a, sprite->colour.v4.r, sprite->colour.v4.g, sprite->colour.v4.b);
    batchVertices[numBatchVerts + 3].x = X;
    batchVertices[numBatchVerts + 3].y = Y - destHeight;
    batchVertices[numBatchVerts + 3].z = sprite->layer;
    batchVertices[numBatchVerts + 3].u = sprite->source_rect.left;
    batchVertices[numBatchVerts + 3].v = sprite->source_rect.bottom;

    /*increase vertex count*/
    numBatchVerts += 4;

    /*Flush buffer if its full*/
    if (numBatchVerts == BATCH_BUFFER_SIZE) {
        /*unlock vertex Buffer*/
        vertexBatchBuffer->Unlock();
        colourModulator->BeginPass(0);
        /*draw quads in the buffer*/
        pd3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numBatchVerts, 0, numBatchVerts / 2);
        colourModulator->EndPass();
        /*reset vertex count*/
        numBatchVerts = 0;
        /*Lock vertex Buffer Again*/
        vertexBatchBuffer->Lock(0, BATCH_BUFFER_SIZE * sizeof(TLVERTEX), (void**) &batchVertices, 0);
    }
}

void endBatchDrawing() {
    /*unlock vertex buffer*/
    vertexBatchBuffer->Unlock();
    colourModulator->BeginPass(0);
    /*draw quads in the buffer*/
    pd3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numBatchVerts, 0, numBatchVerts / 2);
    colourModulator->EndPass();
    /*reset vertex count*/
    numBatchVerts = 0;
    batchDrawingStarted = false;
}

/*creates the bitmask for an imagae based off of the alpha values*/
bool* createBitmask(Sprite* sprite)	{
    D3DLOCKED_RECT rect;
    IDirect3DTexture9* temptexture = (IDirect3DTexture9*)sprite->image->id.p;
    HRESULT hr = temptexture->LockRect(0, &rect, NULL, D3DLOCK_READONLY);
    if (FAILED(hr))
        std::cerr << "ERROR!! MAKING BITMASK" << std::endl;
    bool *bits = new bool[(DWORD)sprite->image->getWidth() * (DWORD)sprite->image->getHeight()];
    for (DWORD y = 0; y < (DWORD)sprite->image->getHeight(); y++) {
        DWORD* Bits = (DWORD*)((BYTE*)rect.pBits + y*rect.Pitch);
        for (DWORD x = 0; x < (DWORD)sprite->image->getWidth(); x++) {
            DWORD pixel = Bits[x];
            bits[y*(DWORD)sprite->image->getWidth() + x] = (pixel&0xff000000) != 0x00;
        }
    }
    temptexture->UnlockRect(0);
    return bits;
}

/*clears the textureSet of all textures*/
void clearTextureList() {
    std::map<std::wstring, Image*>::iterator iter;
    iter = loadedTextures.begin();
    /*iterate through the map deleteing all the textures stored*/
    while (iter != loadedTextures.end()) {
        IDirect3DTexture9* d3dex = (IDirect3DTexture9*)iter->second->id.p;
        if (d3dex != NULL)
            d3dex->Release();
        /*delete the Image* pointer stored in the map*/
        SAFE_DELETE((Image*)iter->second);
        /*delete the reference to the image in the map*/
        loadedTextures.erase(iter);
        iter++;
    }
}

/*remove a texture if the references are less then 2 or decrements the ref counter*/
void unload(Image *image) {
    std::map<Image*, Record*>::iterator iter;
    iter = properties.find(image);
    /*check if passed in arguement exists within the map*/
    if (iter == properties.end()) {
        std::cerr << "Error unloading Image. " << __FILE__ << "at line: "
                  << __LINE__ << " Image not in memory" << std::endl;
        return;
    }
    /*If it exists then check to see if its reference is more then 1*/
    Record *record = iter->second;
    if (record->num_ref > 1)
        /*If it is then decrement the reference*/
        record->num_ref--;
    else {
        /*otherwise release the DirectX texture*/
        IDirect3DTexture9* dxtex = (IDirect3DTexture9*)loadedTextures[record->fileName];
        if (dxtex != NULL)
            dxtex->Release();
        else
            std::cerr << "Error unloading Image. " << __FILE__ << "at line: "
                      << __LINE__ << " DirectX texture is NULL" << std::endl;
        /*delete the record and reference to the object within the maps*/
        loadedTextures.erase(record->fileName);
        properties.erase(iter);
        /*Delete the local declarations*/
        SAFE_DELETE(record);
        SAFE_DELETE(image);
    }
}

void drawCircle( float x, float y, float radius, float r, float g, float b ) {

}

void drawLine( float x, float y, float x_end, float y_end ) {

}

};
