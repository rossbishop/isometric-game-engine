/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sprite.cpp
 * Author: ross
 * 
 * Created on 31 October 2018, 18:38
 */

#include "sprite.h"
#include "renderer.h"

Sprite::Sprite() {
    
}

Sprite::Sprite(Renderer *renderer, const std::string &filePath, const float posX, const float posY, const int sizeX, const int sizeY, int sourceX, int sourceY, uint8_t alpha)
{
    //Origin location in the sheet to display sprite from
    this->_spriteRect.x = sourceX;
    this->_spriteRect.y = sourceY;
    //Width and height of the sprite in the sheet
    this->_spriteRect.w = sizeX;
    this->_spriteRect.h = sizeY;
    
    this->_spriteSheet = SDL_CreateTextureFromSurface(renderer->getRenderer(), renderer->loadImage(filePath));
    if(this->_spriteSheet == NULL)
    {
        printf("\nError: Unable to load image\n");
    }
    
    SDL_SetTextureBlendMode(this->_spriteSheet, SDL_BLENDMODE_BLEND);
    this->setSpriteAlpha(alpha);
    
    this->_currentFrameIndex = 0;
    //Set default animation speed, currently measured in ms
    this->_animationSpeed = 100;
    //Set last animation time
    this->_lastAnimationTicks = SDL_GetTicks();
}

Sprite::~Sprite() {
}

SDL_Texture* Sprite::getSprite()
{
    return this->_spriteSheet;
}

SDL_Rect Sprite::getRect()
{
    return this->_spriteRect;
}

//Alter sprite rect source - used for setting tile locations as well as animations later on
void Sprite::setSpriteRect(int sourceX, int sourceY)
{
    this->_spriteRect.x = sourceX;
    this->_spriteRect.y = sourceY;
}

void Sprite::setSpriteAlpha(uint8_t alpha)
{
    SDL_SetTextureAlphaMod(this->_spriteSheet, alpha);
}

//Draws sprite from sheet at current game position (once lag has been taken into account)
void Sprite::draw(Renderer *renderer, SDL_Texture* spriteSheet, SDL_Rect spriteRect, const float posX, const float posY, double renderSpeed, float dx, float dy, bool isPlayer, float scaleX, float scaleY)
{
    renderer->drawSprite(spriteSheet, spriteRect, posX + (dx * renderSpeed), posY + (dy * renderSpeed), isPlayer, scaleX, scaleY);
}

void Sprite::addAnimation(std::string animationName, animationFrames toAdd)
{
    this->_animations.insert({animationName, toAdd});
}

void Sprite::setCurrentAnimation(std::string animationName)
{
    string lastAnimationString = this->_currentAnimationString;
    this->_currentAnimationString = animationName;
    this->_currentAnimation = this->_animations.at(animationName);
    
    if(lastAnimationString.compare(animationName) != 0)
    {
        this->_lastAnimationTicks = SDL_GetTicks();
        this->_currentFrameIndex = 0;
        this->startNewAnimation();
    }
}

void Sprite::setCurrentFrame(int frameIndex)
{
    this->_spriteRect.x = this->_currentAnimation.at(frameIndex).sourceX;
    this->_spriteRect.y = this->_currentAnimation.at(frameIndex).sourceY;
}

void Sprite::setAnimationSpeed(float speed)
{
    this->_animationSpeed = speed;
}

string Sprite::getCurrentAnimationString()
{
    return this->_currentAnimationString;
}

void Sprite::playAnimation(float dx, float dy)
{
    //Calculate average velocity between x and y - animate at this rate
    float movementAverage = (fabs(dx) + fabs(dy))/2;
    
    //Check if next frame needs to be played - multiply animation speed constant by velocity
    if(SDL_GetTicks() > this->_lastAnimationTicks + (this->_animationSpeed * movementAverage))
    {
        //If current frame is last frame, loop back to frame 0
        if(this->_currentFrameIndex == (this->_currentAnimation.size()-1))
        {
            this->_currentFrameIndex = 0;
        }
        //Otherwise, increment to next frame
        else
        {
            this->_currentFrameIndex++;
        }
        
        this->setCurrentFrame(_currentFrameIndex);
        
        this->_lastAnimationTicks = SDL_GetTicks();
    }
    
}

void Sprite::startNewAnimation()
{
    //Set current frame to first frame of new animation - skip animation delay from playAnimation func in update
    this->setCurrentFrame(0);
}