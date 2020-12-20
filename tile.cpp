/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tile.cpp
 * Author: ross
 * 
 * Created on 19 December 2018, 23:12
 */

#include "tile.h"
#include "renderer.h"
#include "sprite.h"

Tile::Tile() {
}

Tile::Tile(Renderer *renderer, float posX, float posY, const std::string &filepath, int sourceX, int sourceY)
{
    _sprite = Sprite(renderer, filepath, 0, 0, tile_constants::TILE_SIZE_X, tile_constants::TILE_SIZE_Y, 0, 0, 255);
    this->_sourceX, _sourceY = 0;
    this->_posX, _posY = 0;
}

Tile::~Tile() 
{
    
}

void Tile::drawTile(Renderer *renderer, double renderSpeed)
{
    this->_sprite.draw(renderer, this->_sprite.getSprite(), this->_sprite.getRect(), getPosX(), getPosY(), renderSpeed, 0, 0, false, globals::SPRITE_SCALE, globals::SPRITE_SCALE);
}

void Tile::setCoords(int x, int y)
{
    this->_coords.x = x;
    this->_coords.y = y;
    this->_posX = x;
    this->_posY = y;
}

positionStruct Tile::getCoords()
{    
    return this->_coords;
}

Sprite Tile::getSprite()
{
    return this->_sprite;
}

float Tile::getPosX()
{
    return this->_posX;
}

float Tile::getPosY()
{
    return this->_posY; 
}