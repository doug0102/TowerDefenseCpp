//
//  OpenGLColor.h
//  GameDevFramework
//
//  Created by Brad Flood on 11-10-16.
//  Copyright 2011 Algonquin College. All rights reserved.
//

#ifndef OPENGL_COLOR_H
#define OPENGL_COLOR_H


typedef struct OpenGLColor
{
	OpenGLColor(float r, float g, float b, float a)
	{
		red = r;
		green = g;
		blue = b;
		alpha = a;
	}
    
	float red;
	float green;
	float blue;
	float alpha;
}OpenGLColor;


static inline OpenGLColor OpenGLColorRGB(float red, float green, float blue)
{
	return OpenGLColor(red, green, blue, 1.0f);
}

static inline OpenGLColor OpenGLColorRGBA(float red, float green, float blue, float alpha)
{
	return OpenGLColor(red, green, blue, alpha);
}

static inline OpenGLColor OpenGLColorBlack()
{
	return OpenGLColor(0.0f, 0.0f, 0.0f, 1.0f);
}

static inline OpenGLColor OpenGLColorWhite()
{
	return OpenGLColor(1.0f, 1.0f, 1.0f, 1.0f);
}

static inline OpenGLColor OpenGLColorRed()
{
	return OpenGLColor(1.0f, 0.0f, 0.0f, 1.0f);
}

static inline OpenGLColor OpenGLColorGreen()
{
	return OpenGLColor(0.0f, 1.0f, 0.0f, 1.0f);
}

static inline OpenGLColor OpenGLColorBlue()
{
	return OpenGLColor(0.0f, 0.0f, 1.0f, 1.0f);
}

static inline OpenGLColor OpenGLColorCornflowerBlue()
{
	return OpenGLColor(0.3921568627451, 0.5843137254902, 0.9294117647, 1.0f);
}

static inline OpenGLColor OpenGLColorYellow()
{
	return OpenGLColor(1.0f, 1.0f, 0.0f, 1.0f);
}

static inline OpenGLColor OpenGLColorCyan()
{
	return OpenGLColor(0.0f, 1.0f, 1.0f, 1.0f);
}

static inline OpenGLColor OpenGLColorOrange()
{
	return OpenGLColor(1.0f, 0.6471f, 0.0f, 1.0f);
}

static inline OpenGLColor OpenGLColorGray()
{
	return OpenGLColor(0.5f, 0.5f, 0.5f, 1.0f);
}

#endif
