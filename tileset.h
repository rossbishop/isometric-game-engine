/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tileset.h
 * Author: root
 *
 * Created on 21 December 2018, 20:30
 */

#ifndef TILESET_H
#define TILESET_H

#include "tile.h"
#include "json.hpp"
#include <map>
#include <sstream>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
//#include "renderer.h"

class Renderer;

typedef std::map<int, std::string> tilePathMap;
typedef std::map<int, Tile> tileObjectMap;
using json = nlohmann::json;

class Tileset {
public:
    Tileset();
    Tileset(Renderer *renderer, std::string filePath);
    virtual ~Tileset();
    
    Tile getTile(int tileId);
private:
    tilePathMap _tilePaths;
    tileObjectMap _tileObjects;
    std::string _name;
    int _tileCount;
};

#endif /* TILESET_H */

