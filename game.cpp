/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   game.cpp
 * Author: ross
 * 
 * Created on 11 September 2018, 11:23
 */

#include "game.h"
#include "level.h"

Game::Game() 
{
    //Initialise all SDL functions inc. graphics, input, sound etc.
    SDL_Init(SDL_INIT_EVERYTHING);
    
    this->setRunning(true);
    
    //Call main loop to run indefinitely
    this->mainLoop();
}

Game::~Game() 
{
    
}

void Game::mainLoop()
{
    //Create input object
    Input input;
    
    //Create event to check for special input
    SDL_Event event;
    
    //Create renderer to draw with
    Renderer renderer = Renderer();
    
    //Create renderer pointer
    Renderer *rendererPointer = &renderer;
    
    //Create Level - loads level as well
    
    std::string filepath = "content/maps/testmap.json";
    Level level(rendererPointer, filepath);
    
    //Create player object
    this->_player = Player(rendererPointer, 608, 0);
    

    //Set initial time
    double previousTimeMs = SDL_GetTicks();
    
    //Frame time value to be used to calculate whether or not game is lagging
    double lag = 0.0;
    
    int updateCounter = 0;
    int frameCounter = 0;
    double updatePerSecondTimer = SDL_GetTicks();
    double framePerSecondTimer = SDL_GetTicks();
    
    //Infinite loop for game
    while(true)
    {
        //Calculate current time
        double currentTimeMs = SDL_GetTicks();
        //Calculate elapsed time
        double elapsedTimeMs = currentTimeMs - previousTimeMs;
        
        //Set previous time for next loop
        previousTimeMs = currentTimeMs;
        
        //Update lag value
        lag += elapsedTimeMs;
        
        //***PROCESS INPUT HERE***//
        handleInput(event, input, this->_player, this);
        
        if(_isRunning == false) return;
        
        while(lag >= globals::UPDATE_FRAME_TIME)
        {
            //***UPDATE HERE***//
            update(rendererPointer);
            
            lag -= globals::UPDATE_FRAME_TIME;
            
            updateCounter++;
            if(SDL_GetTicks() >= updatePerSecondTimer + 1000)
            {
                //printf("UPS: %d\n", updateCounter);
                updatePerSecondTimer = SDL_GetTicks();
                updateCounter = 0;
            }
        }
        
        //***RENDER HERE***///
        this->draw(rendererPointer, level, (lag/globals::UPDATE_FRAME_TIME));
        
        frameCounter++;
        if(SDL_GetTicks() >= framePerSecondTimer + 1000)
        {
            //printf("FPS: %d\n", frameCounter);
            framePerSecondTimer = SDL_GetTicks();
            frameCounter = 0;
        }
        
        //this->draw(rendererPointer, level, (1));
    }
}

void Game::handleInput(SDL_Event &event, Input &input, Player &player, Game *game)
{
    //Clear previous inputs
    input.beginNewFrame();
    
    //Call input function from input class to 
    input.handleInput(event, input, player, game);
}

void Game::update(Renderer *renderer)
{
    //call all class update functions from here
    this->_player.update(renderer);
}

void Game::draw(Renderer *renderer, Level level, double renderSpeed /*, Level currentLevel*/)
{
    //call all class draw functions from here
    renderer->clear();
    
    level.draw(renderer, renderSpeed); 
    //***renderSpeed is a multiplier of how far to render onwards
    this->_player.draw(renderer, renderSpeed);
    
    renderer->flip();
}

void Game::setRunning(bool running)
{
    (running == false) ? this->_isRunning = false : this->_isRunning = true;
}