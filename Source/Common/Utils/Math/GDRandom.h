//
//  GDRandom.h
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-11-01.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__GDRandom__
#define __GAM_1514_OSX_Game__GDRandom__

#include <functional>
#include <vector>

#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   // constant vector a
#define CMATH_UPPER_MASK 0x80000000 // most significant w-r bits
#define CMATH_LOWER_MASK 0x7fffffff // least significant r bits

#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)


class GDRandom
{
public:
    GDRandom();

	unsigned int random(unsigned int n);
	float random();
    
	void setSeed(unsigned int n);
	unsigned int getSeed();
	unsigned int randomizeSeed();
    
private:
    unsigned int m_Seed;
	unsigned long m_Mt[CMATH_N];
	int m_Index;
};

#endif /* defined(__GAM_1514_OSX_Game__GDRandom__) */
