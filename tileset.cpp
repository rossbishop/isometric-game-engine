/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tileset.cpp
 * Author: root
 * 
 * Created on 21 December 2018, 20:30
 */

#include "tileset.h"

Tileset::Tileset() 
{
    
}

Tileset::Tileset(Renderer *renderer, std::string filePath) 
{
    std::ifstream tempTilesetFileStream(filePath);
    json tempTilesetJson;
    tempTilesetFileStream >> tempTilesetJson;

    this->_tileCount = tempTilesetJson["tilecount"].get<int>();
    this->_name = tempTilesetJson["name"].get<std::string>();
    
    for(int i = 0; i < this->_tileCount; i++)
    {
        
        std::string tileNumber = std::to_string(i);
        std::string contentString = "content";
        std::string tempLocationString = tempTilesetJson["tiles"][tileNumber]["image"].get<std::string>();
        std::string tempStringManip = tempLocationString.substr(2,tempLocationString.size());
        contentString += tempStringManip;
        
        
        /* SOMETHING TO BE DECIDED - may have misconstrued this and need both, not sure atm***
         * Two approaches to storing data in the tileset
         * 1. Store tile numbers and paths in a map inside the tileset
         * 2. Store Tile objects as templates to be used every time a new tile is needed in a level
         */
        
        _tilePaths.insert({i, contentString});     
        
        /* Insert tile object into tileset
         * Since this tileset is essentially just a template
         * posX and posY are irrelevant because they will be set upon being copied into a level
         * sourceX and sourceY are also identical because each tile is its own file
         */
        Tile tempTile = Tile(renderer, 0, 0, contentString, 0, 0);
        
        _tileObjects.insert({i, tempTile});
    }
}

Tileset::~Tileset() 
{
    
}

Tile Tileset::getTile(int tileId)
{
    return _tileObjects.at(tileId);
}