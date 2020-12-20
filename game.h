/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game.h
 * Author: ross
 *
 * Created on 11 September 2018, 11:23
 */

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <cstdlib>
#include "globals.h"
#include "input.h"
#include "renderer.h"
#include "player.h"
//#include "level.h"
#include "tileset.h"

class Level;

class Game 
{
public:
    Game();
    virtual ~Game();
    
    void update(Renderer *renderer);
    void draw(Renderer *renderer, Level levelPointer, double renderSpeed /*, Level currentLevel*/);
    void setRunning(bool running);
private:
    //Main game loop which will run indefinitely when called
    void mainLoop();
    void handleInput(SDL_Event &event, Input &input, Player &player, Game *game);
    
    Player _player;
    bool _isRunning;
};

#endif /* GAME_H */

