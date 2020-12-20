/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   functions.cpp
 * Author: ross
 * 
 * Created on 02 January 2019, 15:16
 */

#include "functions.h"

Functions::Functions() {
}

Functions::Functions(const Functions& orig) {
}

Functions::~Functions() {
}

float Functions::map(float inputVal, float start1, float stop1, float start2, float stop2)
{
    return float(start2 + (stop2-start2) * ((inputVal - start1) / (stop1 - start1)));
}

float Functions::clamp(float inputVal, float lower, float higher)
{
    return float(0);
}
