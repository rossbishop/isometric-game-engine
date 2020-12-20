/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   camera.cpp
 * Author: ross
 * 
 * Created on 02 January 2019, 23:39
 */

#include "camera.h"
#include "globals.h"

Camera::Camera() 
{
    
}

Camera::Camera(float worldOriginX, float worldOriginY) 
{
    //this->_worldPosX = worldOriginX;
    //this->_worldPosY = worldOriginY;
}

Camera::~Camera() 
{
    
}

void Camera::updateWorldPos(float playerPosX, float playerPosY)
{
    this->_cameraX = (playerPosX + (player_constants::PLAYER_SIZE_X/2))-(globals::SCREEN_WIDTH/2);
    this->_cameraY = (playerPosY + (player_constants::PLAYER_SIZE_Y/2))-(globals::SCREEN_HEIGHT/2);
}

float Camera::getCameraX()
{
    return this->_cameraX;
}

float Camera::getCameraY()
{
    return this->_cameraY;
}

