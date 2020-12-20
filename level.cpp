/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   level.cpp
 * Author: ross
 * 
 * Created on 19 December 2018, 23:38
 */

#include "level.h"

namespace level_constants
{
    const int SELECTED_TILESET = 0;
}

Level::Level() 
{
    
}

Level::Level(Renderer *renderer, std::string filepath) 
{
    loadLevel(renderer, filepath);
}

Level::~Level() 
{
    
}

void Level::loadLevel(Renderer *renderer, std::string filepath)
{
    std::ifstream levelFileStream(filepath);
    json fileJson;
    levelFileStream >> fileJson;
    
    //Parse Json file; store all level data in object struct
    parseJsonFile(fileJson, renderer);
    
}

void Level::parseJsonFile(json fileJson, Renderer *renderer)
{
    //Get map height from file 
    this->_levelData.mapheight = fileJson["height"];
    //Get map width from file 
    this->_levelData.mapwidth  = fileJson["width"];
    //Get tile width from file
    this->_levelData.tileWidth = fileJson["tilewidth"];
    //Get tile height from file
    this->_levelData.tileHeight = fileJson["tileheight"];
    //Get next object id from file
    this->_levelData.nextObjectId = fileJson["nextobjectid"];
    //Get infinite bool from file
    this->_levelData.infinite = fileJson["infinite"];
    
    //***LAYER SPECIFIC DATA***//
    
    //Take layer data and split into separate json object 
    json layerJson = fileJson["layers"];
    
    int i = 0;
    
    for(auto layers : layerJson)
    {
        
        layerDataStruct tempLayerDataStruct;
        tempLayerDataStruct.name = layers["name"].get<std::string>(); 
        tempLayerDataStruct.tiles = layers["data"].get<std::vector<int>>();
        tempLayerDataStruct.height = layers["height"].get<int>();
        tempLayerDataStruct.width = layers["width"].get<int>();
        tempLayerDataStruct.xPos = layers["x"].get<int>();
        tempLayerDataStruct.yPos = layers["y"].get<int>();
        tempLayerDataStruct.opacity = layers["opacity"].get<float>();
        tempLayerDataStruct.isVisibile = layers["visible"].get<bool>();
        
        _levelData.levelLayers.insert({i, tempLayerDataStruct});        
        
        i++;

    }
    
    //***TILESET SPECIFIC DATA***//
    
    //Take tileset data and split into separate json object
    json tilesetJson = fileJson["tilesets"];
    
    i = 0;
    
    //Create json object vector
    for(auto tilesets : tilesetJson)
    {
    
        tilesetDataStruct tempTilesetDataStruct;
        
        tempTilesetDataStruct.firstGid = tilesets["firstgid"].get<int>();
        
        std::string tempString = tilesets["source"].get<std::string>();
        //Manipulate source string so it matches source file relative location
        //remove ".."
        std::string tempStringManip = tempString.substr(2,tempString.size());
        tempString = tempStringManip;
        //concatenate "content + tileset/tilesetX.json - path relative to game root directory
        std::string contentString = "content";
        contentString += tempStringManip;
        
        tempTilesetDataStruct.filePath = contentString;
        
        //Load tileset files into JSON objects
        std::ifstream tempTilesetFileStream(contentString);
        json tempTilesetJson;
        tempTilesetFileStream >> tempTilesetJson;
        
        //Load name
        std::string tempName = tempTilesetJson["name"].get<std::string>();
        tempTilesetDataStruct.name = tempName;
        
        //Check against tileset list to see if it already exists
        bool tilesetExists = renderer->doesTilesetExist(tempName);
        
        if(!tilesetExists)
        {
            //Create tileset object from data loaded from json
            Tileset tempTileSet(renderer, tempTilesetDataStruct.filePath);
            
            //Add finished tileset to renderer map
            renderer->addTileset(tempName, tempTileSet);
        }

        //Add finished tileset to level for reference
        _levelData.levelTilesets.insert({i, tempTilesetDataStruct});
        
        i++;
    }
    
    //create current position vector
    posStruct currentCoord;
    currentCoord.x = 0;
    currentCoord.y = 0;
    
    /*
     *  Tilesets stored in level class have member in struct same as key in renderer map
     *  
     *  Need to add each tile from level file id as Tile object in level class
     */
    
    // Loop for number of tile layers in the level
    for(int i = 0; i < this->_levelData.levelLayers.size(); i++)
    {
        // Loop for the number of tiles in each layer
        //for (int j = 0; j < this->_levelData.levelLayers.at(i).tileMapStore.size(); j++)
        for (int j = 0; j < this->_levelData.levelLayers.at(i).tiles.size(); j++)
        {
            int tempId = this->_levelData.levelLayers.at(i).tiles.at(j);
            
            Tileset tempTilesetObject;
            bool found = false;
            int tilesetFirstGid = 0;
            // Check against first gid in tilesets
            for (int k = 0; k < _levelData.levelTilesets.size(); k++)
            {
                // If next tileset = tilesets.end() then set this variable to true
                
                bool lastTileset = false;
                if(k+1 == _levelData.levelTilesets.size()) lastTileset = true;
                
                
                tilesetFirstGid = _levelData.levelTilesets.at(k).firstGid;
                // If id of tile is: 
                //  1. same as or greater than first gid of tileset 
                //  2. and less than first gid of next tileset
                // It resides in this tileset                
                if(tempId >= tilesetFirstGid && ((lastTileset == true) || (tempId < _levelData.levelTilesets.at(k+1).firstGid)))
                {
                    //If conditions are true, grab tileset and save in a temp variable
                   tempTilesetObject = renderer->getTileset(_levelData.levelTilesets.at(k).name);
                   
                   found = true;
                   break;
                }
            }
            
            if(found == false)
            {
                //throw error - tileset couldn't be found
                //maybe just fill with "error tile"?
            }
            
            // Offset layer tile id from x-n format to 0-n format found in files
            int actualTileId = tempId - tilesetFirstGid;
            
            // Retrieve tile
            Tile tempTilesetTile = tempTilesetObject.getTile(actualTileId);
            
            // Add coordinates to tile
            tempTilesetTile.setCoords(currentCoord.x, currentCoord.y);
            
            // Add to layer tile vector - maybe give coordinates (non screenspace) as a member of Tile
            _levelData.levelLayers.at(i).tileObjects.insert({j, tempTilesetTile});
            
            // Increment coordinates
            currentCoord = coordIterator(currentCoord);
        }
        currentCoord.x, currentCoord.y = 0;
    }
    
}

posStruct Level::coordIterator(posStruct toIterate)
{
    toIterate.x++;
    
    //REMOVE HARD CODING, PASS IN LAYER WIDTH
    if(toIterate.x > 9)
    {
        toIterate.x = 0;
        toIterate.y++;
    }
    
    return toIterate;
}

void Level::draw(Renderer *renderer, double renderSpeed)
{
    
    for(int i = 0; i < this->_levelData.levelLayers.size(); i++)
    {
        for(int j = 0; j < this->_levelData.levelLayers.at(i).tileObjects.size(); j++)
        {
            
            // Grab tile, call tile draw function
            Tile *tilePointer = &this->_levelData.levelLayers.at(i).tileObjects.at(j);
            
            // Invoke renderer to draw tile
            renderer->drawTile(tilePointer, renderSpeed, this->_levelData.tileWidth, this->_levelData.tileHeight);
          
        }
    }
}