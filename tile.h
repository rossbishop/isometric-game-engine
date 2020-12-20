/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tile.h
 * Author: ross
 *
 * Created on 19 December 2018, 23:12
 */

#ifndef TILE_H
#define TILE_H
#include <string>
#include "sprite.h"
//#include "renderer.h"
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>

struct positionStruct
{
    int x;
    int y;
};

namespace tile_constants
{
    const int TILE_SIZE_X = 128;
    const int TILE_SIZE_Y = 64;
}

using namespace std;

//include "renderer.h"
class Renderer;
class Sprite;
//class Level;

class Tile
{
public:
    Tile();
    Tile(Renderer *renderer, float posX, float posY, const std::string &filepath, int sourceX, int sourceY);
    virtual ~Tile();
    
    void draw(Renderer *renderer, double renderSpeed);
    float getPosX();
    float getPosY();
    void setPosX();
    void setPosY();
    void setCoords(int x, int y);
    positionStruct getCoords();
    Sprite getSprite();
    void drawTile(Renderer *renderer, double renderSpeed);
private:
    float _posX, _posY, _sourceX, _sourceY;
    positionStruct _coords;
    Sprite _sprite;
};

#endif /* TILE_H */

