/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   renderer.cpp
 * Author: ross
 * 
 * Created on 31 October 2018, 19:30
 */

#include "renderer.h"

Renderer::Renderer() 
{
    //Creates window of width x and height y
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->_gameWindow, &this->_renderer);
    //Sets window title to game name
    SDL_SetWindowTitle(this->_gameWindow, "IsoGameNeu");
}

Renderer::~Renderer() 
{
    SDL_DestroyWindow(this->_gameWindow);
    SDL_DestroyRenderer(this->_renderer);
}

//Empties renderer
void Renderer::clear()
{
    SDL_RenderClear(this->_renderer);
}


//Stores and returns a pointer to an SDL surface mapped to a file location containing an image (e.g. spritesheet)
SDL_Surface* Renderer::loadImage(const std::string& filePath)
{
    /* If image isn't in map, store it
     * 
     * IMG_Load function takes file path (as char array, since it's a C library)
     * Returns an SDL_Surface of that image
     * SDL_Surface gets stored in map under filepath key
     * SDL_Surface is used for software rendering;
     * It will be converted to a SDL_Texture later for rendering
     *  
     */
    if (this->_spriteSheets.count(filePath) == 0) this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
    
    //Return surface of image
    return this->_spriteSheets[filePath];
    
}

//Copy area of texture to area in renderer
void Renderer::blitSurface(SDL_Texture* sourceTexture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle)
{
    /* Bit Block Transfer
     * 
     * Bitwise operation on two or more bitmaps
     * This function takes a single bitmap texture as input
     * An area of that texture is selected
     * And a destination area is selected (in the render output)
     * The pixels in that area are then transferred to the output render
     * 
     */
    SDL_RenderCopy(this->_renderer, sourceTexture, sourceRectangle, destinationRectangle);
}

//Push final render to window
void Renderer::flip()
{
    SDL_RenderPresent(this->_renderer);
}

//Return pointer to renderer - so a copy is not returned and the original can be modified
SDL_Renderer* Renderer::getRenderer() const
{
        return this->_renderer;
}

void Renderer::drawTile(Tile *inputTile, double renderSpeed, int tileWidth, int tileHeight)
{
    // First use renderer function to translate coordinates to screenspace 
    posStruct tempTilePosStruct;
    tempTilePosStruct.x = inputTile->getCoords().x;
    tempTilePosStruct.y = inputTile->getCoords().y;
    
    posStruct tempPosStruct = coordToScreenPosIsometric(tempTilePosStruct, tileWidth, tileHeight);
    
    //Shift by camera position
    tempPosStruct.x -= this->_camera.getCameraX();
    tempPosStruct.y -= this->_camera.getCameraY();
    
    inputTile->setCoords(tempPosStruct.x, tempPosStruct.y);
    
    // Then call tile draw function
    inputTile->drawTile(this, renderSpeed);
}

void Renderer::drawSprite(SDL_Texture* spriteSheet, SDL_Rect &spriteRect, const float posX, const float posY, bool isPlayer, float scaleX, float scaleY)
{
    
    SDL_Rect destinationRectangle;
    
    //We want to constrain the player to the middle of the screen at render time - might change this a little later
    float playerPosX = globals::SCREEN_WIDTH/2;
    float playerPosY = globals::SCREEN_HEIGHT/2;
    
    if(isPlayer)
    {
        destinationRectangle = { posX, (playerPosY-(player_constants::PLAYER_SIZE_Y/2))+posY, spriteRect.w * scaleX, spriteRect.h * scaleY };
    }
    else
    {
        destinationRectangle = { (int)posX, (int)posY, spriteRect.w * scaleX, spriteRect.h * scaleY };
    }
    
    this->blitSurface(spriteSheet, &spriteRect, &destinationRectangle);
}

void Renderer::addTileset(std::string tilesetName, Tileset tilesetAppend)
{
    this->_tilesets.insert({tilesetName, tilesetAppend});
}

bool Renderer::doesTilesetExist(std::string tilesetName)
{
    bool tempbool = (this->_tilesets.find(tilesetName) != this->_tilesets.end()) ? true : false;
    return tempbool;
}

Tileset Renderer::getTileset(std::string tilesetName)
{
    Tileset returnTileset = _tilesets.at(tilesetName);
    return returnTileset;
}

posStruct Renderer::coordToScreenPos(posStruct currentCoord)
{
    posStruct returnStruct;
    
    returnStruct.x = tile_constants::TILE_SIZE_X * currentCoord.x;
    returnStruct.y = tile_constants::TILE_SIZE_Y * currentCoord.y;
    
    return returnStruct;
}

posStruct Renderer::coordToScreenPosIsometric(posStruct currentCoord, int tileWidth, int tileHeight)
{
    posStruct returnStruct;
    
    int screenOffset = (globals::SCREEN_WIDTH/2) - tileWidth/2;
    
    // WRITE ISO ALGO HERE
    returnStruct.x = (currentCoord.x * (tileWidth/2))-(currentCoord.y*(tileWidth/2)) + screenOffset;
    returnStruct.y = ((currentCoord.y) * (tileHeight/2))+(currentCoord.x*(tileHeight/2));
    
    return returnStruct;
}

void Renderer::updateCamera(float playerPosX, float playerPosY)
{
    this->_camera.updateWorldPos(playerPosX, playerPosY);
    
}