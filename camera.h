/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   camera.h
 * Author: ross
 *
 * Created on 02 January 2019, 23:39
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "player.h"

class Camera {
public:
    Camera();
    Camera(float worldOriginX, float worldOriginY);
    virtual ~Camera();
    
    void updateWorldPos(float playerPosX, float playerPosY);
    float getCameraX();
    float getCameraY();
private:
    float _cameraX, _cameraY;
};

#endif /* CAMERA_H */

