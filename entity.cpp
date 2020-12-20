/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   entity.cpp
 * Author: ross
 * 
 * Created on 31 October 2018, 00:49
 */

#include "entity.h"
#include "renderer.h"
#include "globals.h"
#include <algorithm>

using namespace std;

Entity::Entity()
{
    
}

Entity::Entity(Renderer *renderer, const std::string &filePath, const std::string &filePathShadow, float posX, float posY, int sizeX, int sizeY, int sourceX, int sourceY, bool isPlayer)
{
    this->_posX = posX;
    this->_posY = posY;
    this->_posZ = 0;
    this->_dx = 0;
    this->_dy = 0;
    this->_dz = 0;
    this->_isPlayer = isPlayer;
    
    this->_groundHeightZ = 0;
    
    this->_accelJump = 0;
    
    this->_sprite = Sprite(renderer, filePath, posX, posY, sizeX, sizeY, sourceX, sourceY, 255);
    
    if(isPlayer)
    {
        this->_shadowSizeX = 47;
        this->_shadowSizeY = 20;
        
        // add temporary animations - we need to load these in from files afterwards
        animationFrames tempAnimation;
        for(int i = 0; i < 3; i++)
        {
            frame tempFrame;
            tempFrame.sourceX = i * 64;
            tempFrame.sourceY = 0;
            tempAnimation.push_back(tempFrame);
        }
        this->_sprite.addAnimation("Walking Test", tempAnimation);
        
        animationFrames tempAnimation2;
        frame tempFrame;
        // add standing animation
        tempFrame.sourceX = 0;
        tempFrame.sourceY = 0;
        tempAnimation2.push_back(tempFrame);
        this->_sprite.addAnimation("Standing Test", tempAnimation2);
        
        animationFrames tempAnimation3;
        frame tempFrame2;
        // add jumping animation
        tempFrame2.sourceX = 192;
        tempFrame2.sourceY = 0;
        tempAnimation3.push_back(tempFrame2);
        this->_sprite.addAnimation("Jumping Test", tempAnimation3);
        
        //this->_sprite.setCurrentAnimation("Standing Test");
    }
                
    this->_shadowSprite = Sprite(renderer, filePathShadow, posX, posY, this->_shadowSizeX, this->_shadowSizeY, sourceX, sourceY, 233);
    
    this->_shadowScaleX = 1.0f;
    this->_shadowScaleY = 1.0f;
}

Entity::~Entity()
{
    
}

//Return X position of Entity
const float Entity::getPosX()
{
    return this->_posX;
}

//Return Y position of Entity
const float Entity::getPosY()
{
    return this->_posY;
}

const float Entity::getPosZ()
{
    return this->_posZ;
}

const float Entity::getGroundHeightZ()
{
    return this->_groundHeightZ;
}

void Entity::setGroundHeightZ(float zheight)
{
    this->_groundHeightZ = zheight;
}

//Return dy
const float Entity::getdx()
{
    return this->_dx;
}

//Return dx
const float Entity::getdy()
{
    return this->_dy;
}

const float Entity::getdz()
{
    return this->_dz;
}

const float Entity::getPosYActual()
{
    return this->_posYActual;
}

void Entity::setdx(float acceleration, float maxVelocity, incrementOrAbsolute input, bool isJump)
{
    
    if(input == increment)
    {
        this->_dx += acceleration;
        if(this->_dx > maxVelocity) this->_dx = maxVelocity;
        if(this->_dx < -maxVelocity) this->_dx = -maxVelocity;
    }
    if(input == absolute)
    {
        this->_dx = acceleration;
    }
    
    this->_accelX = acceleration;
    
}

void Entity::setdy(float acceleration, float maxVelocity, incrementOrAbsolute input, bool isJump)
{
 
    if(input == increment)
    {

        this->_dy += acceleration;
        if(this->_dy > maxVelocity) this->_dy = maxVelocity;
        if(this->_dy < -maxVelocity) this->_dy = -maxVelocity;

    }
    
    if(input == absolute)
    {
        this->_dy = acceleration;
    } 
   
}

void Entity::setdz(float acceleration, float maxVelocity, incrementOrAbsolute input, bool isJump)
{
    if(input == increment)
    {
        this->_dz += acceleration;
        if(this->_dz > maxVelocity) this->_dz = maxVelocity;
        if(this->_dz < -maxVelocity) this->_dz = -maxVelocity;
    }
    else if(input == absolute)
    {
        this->_dz = acceleration;
    }
    
    this->_accelZ = acceleration;
}

//Set X position of Entity
void Entity::setX(const float value)
{
    this->_posX = value;
}

//Set Y position of Entity
void Entity::setY(const float value)
{
    this->_posY = value;
}

void Entity::setYActual(const float value)
{
    this->_posYActual = value;
}

void Entity::setZ(const float value)
{
    this->_posZ = value;
}

void Entity::setShadowScale(const float x, const float y)
{
    this->_shadowScaleX = x;
    this->_shadowScaleY = y;
}

//Draw Entity to screen at given x/y coordinates with given x and y size
void Entity::draw(Renderer *renderer, double renderSpeed)
{
    
    if(this->_isPlayer)
    {
        float playerPosX = (globals::SCREEN_WIDTH/2)-(player_constants::PLAYER_SIZE_X/2);
        
        this->_shadowSprite.draw(renderer, this->_shadowSprite.getSprite(), this->_shadowSprite.getRect(), playerPosX+((player_constants::PLAYER_SIZE_X/2)-((this->_shadowSizeX/2)*this->_shadowScaleX)), ((player_constants::PLAYER_SIZE_Y)-(this->_shadowSizeY/2)), renderSpeed, getdx(), getdy(), this->_isPlayer, this->_shadowScaleX, this->_shadowScaleY);
        this->_sprite.draw(renderer, this->_sprite.getSprite(), this->_sprite.getRect(), playerPosX, getPosY()-getPosYActual(), renderSpeed, getdx(), getdy(), this->_isPlayer, globals::SPRITE_SCALE, globals::SPRITE_SCALE);
    }
    else
    {
        this->_sprite.draw(renderer, this->_sprite.getSprite(), this->_sprite.getRect(), getPosX(), getPosY(), renderSpeed, getdx(), getdy(), this->_isPlayer, globals::SPRITE_SCALE, globals::SPRITE_SCALE);
    }
}

void Entity::update(Renderer *renderer)
{
    setZ(getPosZ()+(getdz()/*+(this->_accelZ)/2*/));
    
    if(this->getPosZ() <= this->_groundHeightZ)
    {
        this->setZ(_groundHeightZ);
    }
    
    if(this->getPosZ() > this->_groundHeightZ)
    {
        this->setYActual(getPosY()+getPosZ());
        
        float dz = this->getdz();
        float dy = this->getdy();
        float accumulatedAccel = (dy + (-dz));  
        
        this->setY(getPosY()+accumulatedAccel);
    }
    else
    {
        setY(getPosY()+(getdy()));
        this->setYActual(getPosY()-getdy());
    }
    
    setX(getPosX()+(getdx()));
    
    if(this->_isPlayer)
    {
        renderer->updateCamera(this->_posX, this->_posYActual);
        this->_sprite.playAnimation(this->_dx, this->_dy);
    }
    
    //printf("dx: %f\n", this->_dx);
    //printf("dy: %f\n", this->_dy);
}