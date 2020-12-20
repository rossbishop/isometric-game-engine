/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   renderer.h
 * Author: ross
 *
 * Created on 31 October 2018, 19:30
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "globals.h"
#include "tileset.h"
#include "tile.h"
#include "camera.h"
#include "player.h"

typedef std::map<std::string, Tileset> tilesetMap;

struct posStruct
{
    int x;
    int y;
};

class Renderer 
{
public:
    Renderer();
    virtual ~Renderer();
    
    void clear();
    
    SDL_Renderer* getRenderer() const;
    
    SDL_Surface* loadImage(const std::string &filePath);
    void blitSurface(SDL_Texture* sourceTexture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);
    void flip();
    
    void drawTile(Tile *inputTile, double renderSpeed, int tileWidth, int tileHeight);
    void drawSprite(SDL_Texture* spriteSheet, SDL_Rect &spriteRect, const float posX, const float posY, bool isPlayer, float scaleX, float scaleY);
    
    void addTileset(std::string tilesetName, Tileset tilesetAppend);
    Tileset getTileset(std::string tilesetName);
    bool doesTilesetExist(std::string tilesetName);
    
    posStruct coordToScreenPos(posStruct currentCoord);
    posStruct coordToScreenPosIsometric(posStruct currentCoord, int tileWidth, int tileHeight);
    
    void updateCamera(float playerPosX, float playerPosY);
private:

    SDL_Window* _gameWindow;
    SDL_Renderer* _renderer;
    Camera _camera;
    Player* _playerPointer;
    
    //map of filepaths against Surfaces (spritesheets)
    std::map<std::string, SDL_Surface*> _spriteSheets;
    tilesetMap _tilesets;
    
};

#endif /* RENDERER_H */

