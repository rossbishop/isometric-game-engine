/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.h
 * Author: ross
 *
 * Created on 31 October 2018, 17:20
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "globals.h"
#include "functions.h"
#include <tgmath.h>
#include <cmath>

namespace player_constants
{
    const int PLAYER_SIZE_X = 64;
    const int PLAYER_SIZE_Y = 128;
    const float DIAG_ANGLE = 0.453786f;
    
    const float MAX_VELOCITY_PER_UPDATE      = 1.0f   * globals::UPDATE_SCALAR;   // 1.0 pixels per update,  120 pixels/second at native 120UPS
    const float MAX_JUMP_VELOCITY_PER_UPDATE = 1.0f   * globals::UPDATE_SCALAR;   // 1.0 pixels per update
    const float TERMINAL_VELOCITY            = 2.0f   * globals::UPDATE_SCALAR;
    
    const float MOVE_ACCELERATION_PER_UPDATE = 0.02f  * globals::UPDATE_SCALAR;   // 0.02 pixels per update, 2.4 pixels/second/second at native 120UPS
    const float MOVE_DECELERATION_PER_UPDATE = 0.01f  * globals::UPDATE_SCALAR;   // 0.01 pixels per update, 1.2 pixels/second/second at native 120UPS
    
    const float MAX_JUMP_HEIGHT              = 256.0f * globals::UPDATE_SCALAR;
    const float PEAK_JUMP_DISTANCE           = 256.0f * globals::UPDATE_SCALAR;
    const float PEAK_JUMP_TIME               = (PEAK_JUMP_DISTANCE / MAX_VELOCITY_PER_UPDATE) * globals::UPDATE_SCALAR;
    const float GRAVITY_ACCELERATION         = 2*MAX_JUMP_HEIGHT*pow(MAX_VELOCITY_PER_UPDATE,2)/pow(PEAK_JUMP_DISTANCE,2);

}

enum facingDirection
{
    facingUp,
    facingDown,
    facingLeft,
    facingRight,
    facingUpRight,
    facingUpLeft,
    facingDownRight,
    facingDownLeft
};

class Player : public Entity
{
public:
    Player();
    Player(Renderer *renderer, float posX, float posY);
    virtual ~Player();
    
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void moveUpRight();
    void moveUpLeft();
    void moveDownRight();
    void moveDownLeft();
    void jump(bool isHeld);
    bool isJumping();
    void setJumping(bool jumping);
    void stop(bool dx, bool dy, bool collisionX, bool collisionY);
    void printVelocity();
    
private:
    facingDirection _facing;

    bool _isWalking;
    bool _isJumping;
    bool _isFalling;

};

#endif /* PLAYER_H */

