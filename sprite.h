/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sprite.h
 * Author: ross
 *
 * Created on 31 October 2018, 18:38
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <vector>
#include <map>

//#include "renderer.h"

struct frame
{
    int sourceX;
    int sourceY;
};

using namespace std;

typedef std::vector<frame> animationFrames;
typedef std::map<std::string, animationFrames> animationMap;

class Renderer;

class Sprite {
public:
    Sprite();
    Sprite(Renderer *renderer, const std::string &filePath, const float posX, const float posY, const int sizeX, const int sizeY, int sourceX, int sourceY, uint8_t alpha);
    virtual ~Sprite();
    
    SDL_Rect getRect();
    SDL_Texture* getSprite();
    void draw(Renderer *renderer, SDL_Texture* spriteSheet, SDL_Rect spriteRect, const float posX, const float posY, double renderSpeed, float dx, float dy, bool isPlayer, float scaleX, float scaleY);
    void setSpriteRect(int sourceX, int sourceY);
    void setSpriteAlpha(uint8_t alpha);
    
    void addAnimation(std::string animationName, animationFrames toAdd);
    void setCurrentAnimation(std::string animationName);
    void setCurrentFrame(int frameIndex);
    void setAnimationSpeed(float speed);
    string getCurrentAnimationString();
    void playAnimation(float dx, float dy);
    void startNewAnimation();
protected:
    SDL_Rect _spriteRect;
    SDL_Texture* _spriteSheet;
    
    animationMap _animations;
    animationFrames _currentAnimation;
    string _currentAnimationString;
    int _currentFrameIndex;
    float _animationSpeed;
    int _lastAnimationTicks;

private:

};

#endif /* SPRITE_H */

