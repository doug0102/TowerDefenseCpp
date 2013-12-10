//
//  OpenGLTexture.h
//  GameDevFramework
//
//  Created by Brad Flood on 11-10-16.
//  Copyright 2011 Algonquin College. All rights reserved.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "OpenGLColor.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
    #if TARGET_OS_IPHONE
        #include <OpenGLES/ES1/gl.h>
        #include <OpenGLES/ES1/glext.h>
    #elif TARGET_OS_MAC
        #include <OpenGL/OpenGL.h>
        #include <OpenGL/gl.h>
    #endif
#else
    #include <Windows.h>
    #include "GL/gl.h"
#endif

#include <string>
#include <stdlib.h>



class OpenGLTextureInfo
{
public:
    OpenGLTextureInfo();
    OpenGLTextureInfo(const OpenGLTextureInfo& textureData);
    
    unsigned int sourceX;
    unsigned int sourceY;
    unsigned int sourceWidth;
    unsigned int sourceHeight;
    unsigned int textureWidth;
    unsigned int textureHeight;
    unsigned int textureFormat;
    unsigned int textureId;
    std::string textureFilename;
    std::string atlasKey;
};


class OpenGLTexture
{
public:
    OpenGLTexture(const char* filename, const char* atlasKey = NULL);
    OpenGLTexture(OpenGLTextureInfo* textureInfo);
    virtual ~OpenGLTexture();
    
	unsigned int getFormat();
	unsigned int getId();
    
	virtual unsigned int getSourceX();
	virtual unsigned int getSourceY();
	virtual unsigned int getSourceWidth();
	virtual unsigned int getSourceHeight();
    
	unsigned int getTextureWidth();
	unsigned int getTextureHeight();
    
    std::string getFilename();
    std::string getAtlasKey();
    
    void setColor(OpenGLColor color);
    OpenGLColor getColor();
    
    void setAlpha(float alpha);
	float getAlpha();
    
    virtual bool isAnimated();
    
    void setAnchorPoint(float x, float y);
    float getAnchorPointX();
    float getAnchorPointY();
    
protected:
    friend class OpenGLFont;
    friend class OpenGLAnimatedTexture;
    friend class OpenGLTextureManager;
    
    void setTextureInfo(OpenGLTextureInfo* textureInfo);
    OpenGLTextureInfo* getTextureInfo();
    
    OpenGLTextureInfo* m_TextureInfo;
    OpenGLColor m_Color;
    float m_AnchorX;
    float m_AnchorY;
};

#endif
