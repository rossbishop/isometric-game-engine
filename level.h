/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   level.h
 * Author: ross
 *
 * Created on 19 December 2018, 23:38
 */

#ifndef LEVEL_H
#define LEVEL_H

#include "renderer.h"
#include "tile.h"
#include "json.hpp"
#include "game.h"
#include <sstream>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
using json = nlohmann::json;

typedef std::map<int, Tile> tileMap;
typedef vector<int> tileIds;
typedef std::map<int, tileMap> layerTileMap;

struct layerDataStruct
{
    std::string name;
    int width;
    int height;
    float opacity;
    int xPos;
    int yPos;
    bool isVisibile;
    tileIds tiles;
    tileMap tileObjects;
};

struct tilesetDataStruct
{
    std::string name;
    std::string filePath;
    int firstGid;
};

typedef vector<int> layer;
typedef std::map<int, layerDataStruct> layerMap;
typedef std::map<int, tilesetDataStruct> tilesetStructMap;

struct levelDataStruct
{
    int mapheight;
    int mapwidth;
    int tileWidth;
    int tileHeight;
    int nextObjectId;
    bool infinite;
     
    //layer data
    layerMap levelLayers;
    
    //tileset data
    tilesetStructMap levelTilesets;
    
};

class Level {
public:
    Level();
    Level(Renderer *renderer, std::string filepath);
    virtual ~Level();
    
    void loadLevel(Renderer *renderer, std::string filepath);
    void parseJsonFile(json fileJson, Renderer *renderer);
    posStruct coordIterator(posStruct toIterate);
    void draw(Renderer *renderer, double renderSpeed);
private:
    levelDataStruct _levelData; 
    int _layerCount;

};

#endif /* LEVEL_H */

