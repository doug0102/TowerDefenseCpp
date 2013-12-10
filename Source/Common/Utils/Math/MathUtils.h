//
//  MathUtils.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-01-09.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

//min and max defines for windows only
#if WIN32
#define fminf(a,b) ((a) < (b) ? (a) : (b))
#define fmaxf(a,b) ((a) > (b) ? (a) : (b))
#endif


class MathUtils
{
public:
    //Returns a number to the nearest power of 2
    static unsigned int nextPowerOf2(unsigned int value);
    
    //Degrees and radians conversion functions
    static float radiansToDegrees(float radians);
    static float degressToRadians(float degrees);
    
    //Are 2 values within a certain range with each other
    static bool withinRange(float valueA, float valueB, float range); 
};

#endif
