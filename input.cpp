/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   input.cpp
 * Author: ross
 * 
 * Created on 03 October 2018, 03:29
 */

#include "input.h"
#include "game.h"

Input::Input() 
{
}

Input::~Input() 
{
}

void Input::handleInput(SDL_Event &event, Input &input, Player &player, Game *game)
{
    //Poll event to see if any changes have occurred
    if (SDL_PollEvent(&event))
    {
        //If a key has been pressed...
        if(event.type == SDL_KEYDOWN)
        {
            
            //If the key isn't repeating...
            if(event.key.repeat == 0)
            {
                //Register as a key down event
                keyDownEvent(event);
            }
        }
        //If a key has been released...
        else if (event.type == SDL_KEYUP)
        {
            //Register as a key up event
            keyUpEvent(event);
        }
        //If quit event is triggered...
        else if (event.type == SDL_QUIT)
        {
            //Exit program
            game->setRunning(false);
        }
        
        //If escape key is pressed...
        if (wasKeyPressed(SDL_SCANCODE_ESCAPE))
        {
            //Exit program
            game->setRunning(false);
        }
        
    }
    
        //if (isKeyHeld(_lastState.key1) && isKeyHeld(_lastState.key2))
        //{
            //do nothing - keep things the same
               
        //}
        if (isKeyHeld(SDL_SCANCODE_W) && isKeyHeld(SDL_SCANCODE_D))
        {
            //Clear other held keys
            //this->_heldKeys.clear();
            //this->_heldKeys.
            player.moveUpRight();
            _lastState.key1 = SDL_SCANCODE_UP;
            _lastState.key2 = SDL_SCANCODE_RIGHT;
            
        }
        else if (isKeyHeld(SDL_SCANCODE_W) && isKeyHeld(SDL_SCANCODE_A))
        {
            player.moveUpLeft();
            _lastState.key1 = SDL_SCANCODE_UP;
            _lastState.key2 = SDL_SCANCODE_LEFT;
        }
        else if (isKeyHeld(SDL_SCANCODE_S) && isKeyHeld(SDL_SCANCODE_D))
        {
            player.moveDownRight();
            _lastState.key1 = SDL_SCANCODE_DOWN;
            _lastState.key2 = SDL_SCANCODE_RIGHT;
        }
        else if (isKeyHeld(SDL_SCANCODE_S) && isKeyHeld(SDL_SCANCODE_A))
        {
            player.moveDownLeft();
            _lastState.key1 = SDL_SCANCODE_DOWN;
            _lastState.key2 = SDL_SCANCODE_LEFT;
        }    
        else if (isKeyHeld(SDL_SCANCODE_W))
        {
            player.moveUp();
            _lastState.key1 = SDL_SCANCODE_UP;
            _lastState.key2 = SDL_SCANCODE_0;
        }
        else if (isKeyHeld(SDL_SCANCODE_S))
        {
            player.moveDown();
            _lastState.key1 = SDL_SCANCODE_DOWN;
            _lastState.key2 = SDL_SCANCODE_0;
        }
        else if (isKeyHeld(SDL_SCANCODE_D))
        {
            player.moveRight();
            _lastState.key1 = SDL_SCANCODE_RIGHT;
            _lastState.key2 = SDL_SCANCODE_0;
        }
        else if (isKeyHeld(SDL_SCANCODE_A))
        {
            player.moveLeft();
            _lastState.key1 = SDL_SCANCODE_LEFT;
            _lastState.key2 = SDL_SCANCODE_0;
            
        }
        else if (!isKeyHeld(SDL_SCANCODE_W) && !isKeyHeld(SDL_SCANCODE_S) && !isKeyHeld(SDL_SCANCODE_D) && !isKeyHeld(SDL_SCANCODE_A))
        {
            
            if(player.isJumping())
            {
                player.stop(false, false, false, false);
            }
            else
            {
                player.stop(true, true, false, false);
            }
            //clear last state
            _lastState.key1 = SDL_SCANCODE_0;
            _lastState.key2 = SDL_SCANCODE_0;
        }
    
    if(isKeyHeld(SDL_SCANCODE_J))
    {
        player.setJumping(false);
    }
    
    //jump + fall code;
    if(isKeyHeld(SDL_SCANCODE_SPACE))
    {
        player.jump(true);
    }
    else if(wasKeyReleased(SDL_SCANCODE_SPACE))
    {
        player.jump(false);
    }
    else if(player.isJumping())
    {
        player.jump(false);
    }
}

//Clears input state every new frame
void Input::beginNewFrame()
{
    this->_pressedKeys.clear();
    this->_releasedKeys.clear();
}

//Called when a key is pressed
void Input::keyDownEvent(const SDL_Event &event)
{
    //Key added to pressed and held arrays as true when key is initially pressed
    this->_pressedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = true;
}

//Called when a key is released
void Input::keyUpEvent(const SDL_Event &event)
{
    //Key added to released array as true but removed from held array as it has been released
    this->_releasedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = false;
}

//Called to check whether a given key has been pressed
bool Input::wasKeyPressed(SDL_Scancode key)
{
    //Returns boolean value of given key
    return this->_pressedKeys[key];
}

//Called to check whether a given key has been released
bool Input::wasKeyReleased(SDL_Scancode key)
{
    //Returns boolean value of given key
    return this->_releasedKeys[key];
}

//Called to check whether a given key is being held
bool Input::isKeyHeld(SDL_Scancode key)
{
    //Returns boolean value of given key
    return this->_heldKeys[key];
}