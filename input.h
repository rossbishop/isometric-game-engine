/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   input.h
 * Author: ross
 *
 * Created on 03 October 2018, 03:29
 */

#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL.h>

#include "player.h"

class Game;

struct lastStateStruct
{
    SDL_Scancode key1;
    SDL_Scancode key2;
};

class Input {
public:
    Input();
    virtual ~Input();
    void handleInput(SDL_Event &event, Input &input, Player &player, Game *game);
    void beginNewFrame();
    void keyDownEvent(const SDL_Event& event);
    void keyUpEvent(const SDL_Event &event);
    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);
private:
    //Maps of key scan codes against booleans
    std::map<SDL_Scancode, bool> _heldKeys;
    std::map<SDL_Scancode, bool> _pressedKeys;
    std::map<SDL_Scancode, bool> _releasedKeys;
    lastStateStruct _lastState;

};

#endif /* INPUT_H */

