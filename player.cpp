/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.cpp
 * Author: ross
 * 
 * Created on 31 October 2018, 17:20
 */

#include "player.h"

Player::Player() 
{
    
}

Player::Player(Renderer *renderer, float posX, float posY) : 
        Entity(renderer, "content/sprites/player.png", "content/sprites/playershadow.png", posX, posY, player_constants::PLAYER_SIZE_X, player_constants::PLAYER_SIZE_Y, 0, 0, true)
{
    this->_isJumping = false;
}

Player::~Player() 
{
    
}

void Player::moveUp()
{
    this->setdy(-player_constants::MOVE_ACCELERATION_PER_UPDATE, player_constants::MAX_VELOCITY_PER_UPDATE, increment, false); 
    this->stop(true, false, false, false);
    this->_facing = facingUp;
    this->_isWalking = true;
    if(this->_isJumping == true || this->_isFalling == true)
    {
        this->_sprite.setCurrentAnimation("Jumping Test");
    }
    else
    {
        bool changed = false;
        this->_sprite.setCurrentAnimation("Walking Test");
    }
    
}

void Player::moveDown()
{
    this->setdy(player_constants::MOVE_ACCELERATION_PER_UPDATE, player_constants::MAX_VELOCITY_PER_UPDATE, increment, false);
    this->stop(true, false, false, false);
    this->_facing = facingDown;
    this->_isWalking = true;
    if(this->_isJumping == true || this->_isFalling == true)
    {
        this->_sprite.setCurrentAnimation("Jumping Test");
    }
    else
    {
        this->_sprite.setCurrentAnimation("Walking Test");
    }
}

void Player::moveLeft()
{

    this->setdx(-player_constants::MOVE_ACCELERATION_PER_UPDATE, player_constants::MAX_VELOCITY_PER_UPDATE, increment, false);
    this->stop(false, true, false, false);
    this->_facing = facingLeft;
    this->_isWalking = true;
    if(this->_isJumping == true || this->_isFalling == true)
    {
        this->_sprite.setCurrentAnimation("Jumping Test");
    }
    else
    {
        this->_sprite.setCurrentAnimation("Walking Test");
    }

}

void Player::moveRight()
{

    this->setdx(player_constants::MOVE_ACCELERATION_PER_UPDATE, player_constants::MAX_VELOCITY_PER_UPDATE, increment, false);
    this->stop(false, true, false, false);
    this->_facing = facingRight;
    this->_isWalking = true;
    if(this->_isJumping == true || this->_isFalling == true)
    {
        this->_sprite.setCurrentAnimation("Jumping Test");
    }
    else
    {
        this->_sprite.setCurrentAnimation("Walking Test");
    }

}

void Player::moveUpRight()
{
    this->setdx(player_constants::MOVE_ACCELERATION_PER_UPDATE, (player_constants::MAX_VELOCITY_PER_UPDATE)*cos(player_constants::DIAG_ANGLE), increment, false);
    this->setdy(-player_constants::MOVE_ACCELERATION_PER_UPDATE, (player_constants::MAX_VELOCITY_PER_UPDATE)*sin(player_constants::DIAG_ANGLE), increment, false);
    
    this->_facing = facingUpRight;
    this->_isWalking = true;
    if(this->_isJumping == true || this->_isFalling == true)
    {
        this->_sprite.setCurrentAnimation("Jumping Test");
    }
    else
    {
        this->_sprite.setCurrentAnimation("Walking Test");
    }
}

void Player::moveUpLeft()
{
    this->setdx(-player_constants::MOVE_ACCELERATION_PER_UPDATE, (player_constants::MAX_VELOCITY_PER_UPDATE)*cos(player_constants::DIAG_ANGLE), increment, false);
    this->setdy(-player_constants::MOVE_ACCELERATION_PER_UPDATE, (player_constants::MAX_VELOCITY_PER_UPDATE)*sin(player_constants::DIAG_ANGLE), increment, false);
    
    this->_facing = facingUpLeft;
    this->_isWalking = true;
    if(this->_isJumping == true || this->_isFalling == true)
    {
        this->_sprite.setCurrentAnimation("Jumping Test");
    }
    else
    {
        this->_sprite.setCurrentAnimation("Walking Test");
    }
}

void Player::moveDownRight()
{  
    this->setdx(player_constants::MOVE_ACCELERATION_PER_UPDATE, (player_constants::MAX_VELOCITY_PER_UPDATE)*cos(player_constants::DIAG_ANGLE), increment, false);
    this->setdy(player_constants::MOVE_ACCELERATION_PER_UPDATE, (player_constants::MAX_VELOCITY_PER_UPDATE)*sin(player_constants::DIAG_ANGLE), increment, false);
    
    this->_facing = facingDownRight;
    this->_isWalking = true;
    if(this->_isJumping == true || this->_isFalling == true)
    {
        this->_sprite.setCurrentAnimation("Jumping Test");
    }
    else
    {
        this->_sprite.setCurrentAnimation("Walking Test");
    }
}

void Player::moveDownLeft()
{   
    this->setdx(-player_constants::MOVE_ACCELERATION_PER_UPDATE, (player_constants::MAX_VELOCITY_PER_UPDATE)*cos(player_constants::DIAG_ANGLE), increment, false);
    this->setdy(player_constants::MOVE_ACCELERATION_PER_UPDATE, (player_constants::MAX_VELOCITY_PER_UPDATE)*sin(player_constants::DIAG_ANGLE), increment, false);
  
    this->_facing = facingDownLeft;
    this->_isWalking = true;
    if(this->_isJumping == true || this->_isFalling == true)
    {
        this->_sprite.setCurrentAnimation("Jumping Test");
    }
    else
    {
        this->_sprite.setCurrentAnimation("Walking Test");
    }
}

void Player::jump(bool isHeld)
{
    
    if(!this->_isJumping)
    {
        this->setdz(player_constants::MAX_JUMP_VELOCITY_PER_UPDATE, player_constants::MAX_JUMP_VELOCITY_PER_UPDATE, absolute, true);
        this->_isJumping = true;
        this->_isWalking = false;
        this->_sprite.setCurrentAnimation("Jumping Test");
    }
    if(isHeld)
    {
        this->setdz(player_constants::MAX_JUMP_VELOCITY_PER_UPDATE, player_constants::MAX_JUMP_VELOCITY_PER_UPDATE, absolute, true); 
    }
    else if(!isHeld)
    {
        // If player has hit the ground then stop jumping
        if(this->getPosZ() <= this->getGroundHeightZ())
        {
            this->_isJumping = false;
            this->_isFalling = false;
        }
        // If player hasn't hit the ground, then fall - may want to actually move this functionality to a "gravity/fall" method
        else
        {
            this->setdz(-player_constants::GRAVITY_ACCELERATION, player_constants::TERMINAL_VELOCITY, increment, true); 
            this->_isFalling = true;
        }
    }
    
    int start1 = 0;
    int start2 = 191;
    int stop1 = player_constants::MAX_JUMP_HEIGHT;
    int stop2 = 0;
    
    Functions tempFunction;
    
    float shadowAlpha = tempFunction.map(this->getPosZ(), start1, stop1, start2, stop2);
    int shadowAlphaInt = int(shadowAlpha);
    
    this->_shadowSprite.setSpriteAlpha(shadowAlphaInt);
    
    start1 = 0;
    start2 = 1.0f;
    stop1 = player_constants::MAX_JUMP_HEIGHT;
    stop2 = 3.0f;
    
    float spriteScale = tempFunction.map(this->getPosZ(), start1, stop1, start2, stop2);
    
    this->setShadowScale(spriteScale, spriteScale);
    
}

bool Player::isJumping()
{
    return this->_isJumping;
}

void Player::setJumping(bool jumping)
{
    this->_isJumping = jumping;
}

void Player::stop(bool dx, bool dy, bool collisionX, bool collisionY)
{
    
    // If player isn't moving at all then make "isWalking" false
    if(dx && dy)
    {
        if(this->getdx() == 0 && this->getdy() == 0)
        {
            this->_isWalking = false;
            this->_sprite.setCurrentAnimation("Standing Test");
            this->_sprite.startNewAnimation();
        }
    }
    
    if(dx)
    {
        if(collisionX)
        {
            this->setdx(0, 0, absolute, false);
        }
        else
        {
            if(this->getdx() < 0)
            {
                // If velocity is around one increment then clamp at 0, to stop player "floating" around
                if(this->getdx() <= 0 && this->getdx() > -player_constants::MOVE_DECELERATION_PER_UPDATE*2)
                {
                    this->setdx(0, 0, absolute, false);
                }
                else
                {
                    this->setdx(player_constants::MOVE_DECELERATION_PER_UPDATE, player_constants::MAX_VELOCITY_PER_UPDATE, increment, false);
                }
            }
            else
            {
                if(this->getdx() <= 0 && this->getdx() < player_constants::MOVE_DECELERATION_PER_UPDATE*2)
                {
                    this->setdx(0, 0, absolute, false);
                }
                else
                {
                    this->setdx(-player_constants::MOVE_DECELERATION_PER_UPDATE, player_constants::MAX_VELOCITY_PER_UPDATE, increment, false);
                }
            } 
        }

    }
     
    if(dy)
    {
        if(collisionY)
        {
            this->setdy(0, 0, absolute, false);
        }
        else
        {
            if(this->getdy() < 0)
            {

                // If velocity is around one increment then clamp at 0, to stop player "floating" around
                if(this->getdy() <= 0 && this->getdy() > -player_constants::MOVE_DECELERATION_PER_UPDATE*2)
                {
                    this->setdy(0, 0, absolute, false);
                }
                else
                {
                    this->setdy(player_constants::MOVE_DECELERATION_PER_UPDATE, player_constants::MAX_VELOCITY_PER_UPDATE, increment, false);
                }
            }
            else
            {
                if(this->getdy() <= 0 && this->getdy() < player_constants::MOVE_DECELERATION_PER_UPDATE*2)
                {
                    this->setdy(0, 0, absolute, false);
                }
                else
                {
                    this->setdy(-player_constants::MOVE_DECELERATION_PER_UPDATE, player_constants::MAX_VELOCITY_PER_UPDATE, increment, false);
                }
            } 
        }
            
    }

}

void Player::printVelocity()
{
    printf("dx: %f\n", this->getdx());
    printf("dy: %f\n", this->getdy());
}
