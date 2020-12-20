/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   entity.h
 * Author: ross
 *
 * Created on 31 October 2018, 00:49
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "sprite.h"
//#include "renderer.h"

class Renderer;

enum incrementOrAbsolute
{
    absolute,
    increment
};

class Entity
{
public: 
    Entity();
    Entity(Renderer *renderer, const std::string &filePath, const std::string &filePathShadow, float posX, float posY, int sizeX, int sizeY, int sourceX, int sourceY, bool isPlayer);
    virtual ~Entity();
    
    void update(Renderer *renderer);
    void draw(Renderer *renderer, double renderSpeed);
    
    const float getPosX();
    const float getPosY();
    const float getPosZ();
    const float getdx();
    const float getdy();
    const float getdz();
    const float getGroundHeightZ();
    const float getPosYActual();
    const int getSizeX();
    const int getSizeY();
    
    void setdx(const float acceleration, const float maxVelocity, incrementOrAbsolute input, bool isJump);
    void setdy(const float acceleration, const float maxVelocity, incrementOrAbsolute input, bool isJump);
    void setdz(const float acceleration, const float maxVelocity, incrementOrAbsolute input, bool isJump);
    void setX(const float value);
    void setXActual(const float value);
    void setY(const float value);
    void setYActual(const float value);
    void setZ(const float value);
    void setGroundHeightZ(float zheight);
    void setSpriteScale(const float x, const float y);
    void setShadowScale(const float x, const float y);
    
protected:
    Sprite _sprite;
    Sprite _shadowSprite;
    
private:
    float _posX, _posY, _posYActual ,_posZ, _groundHeightZ, _dx, _dy, _dz, _accelX, _accelY, _accelZ, _accelJump, _shadowScaleX, _shadowScaleY, _shadowSizeX, _shadowSizeY;
    bool _isPlayer;
    
};

#endif /* ENTITY_H */
