/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   functions.h
 * Author: ross
 *
 * Created on 02 January 2019, 15:16
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class Functions {
public:
    Functions();
    Functions(const Functions& orig);
    virtual ~Functions();
    
    float map(float inputVal, float start1, float stop1, float start2, float stop2);
    float clamp(float inputVal, float lower, float higher);
private:

};

#endif /* FUNCTIONS_H */

