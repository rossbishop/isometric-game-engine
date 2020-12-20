/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   globals.h
 * Author: ross
 *
 * Created on 11 September 2018, 17:50
 */

#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals
{
    const float NATIVE_SPEED = 120.0f;         // Native game UPS design
    const float MAX_UPDATES_PER_SECOND = 120.0f;  // Game update rate (calculation frames per second)
    const float UPDATE_SCALAR = NATIVE_SPEED/MAX_UPDATES_PER_SECOND;
    
    //Number of ms per update
    const double UPDATE_FRAME_TIME = 1000/MAX_UPDATES_PER_SECOND;
    
    //Screen width in pixels
    const int SCREEN_WIDTH = 1280;
    
    //Screen height in pixels
    const int SCREEN_HEIGHT = 640;
    
    //Global sprite scalar
    const float SPRITE_SCALE = 1.0f;
}

#endif /* GLOBALS_H */

