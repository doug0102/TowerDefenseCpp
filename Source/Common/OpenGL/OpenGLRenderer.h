//
//  OpenGLRenderer.h
//  GameDevFramework
//
//  Created by Bradley Flood on 12-08-30.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

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
#elif WIN32
#include <Windows.h>
#include "GL/gl.h"
#endif

class OpenGLTexture;

class OpenGLRenderer
{
public:
    static OpenGLRenderer* getInstance();
    static void cleanupInstance();
    
    void clear();
    
    OpenGLColor getBackgroundColor();
    void setBackgroundColor(OpenGLColor backgroundColor);
    
    OpenGLColor getForegroundColor();
    void setForegroundColor(OpenGLColor foregroundColor);
    
    void enableClip(float x, float y, float width, float height);
    void disableClip();
    
    void enableBlending(unsigned int sourceBlending = GL_SRC_ALPHA, unsigned int destinationBlending = GL_ONE_MINUS_SRC_ALPHA);
    void disableBlending();
    
    float getPointSize();
    void setPointSize(float pointSize);
    void resetPointSize();
    
    float getLineWidth();
    void setLineWidth(float lineWidth);
    void resetLineWidth();
    
    void drawPoint(float x, float y);
    void drawLine(float x1, float y1, float x2, float y2);
    
    void drawCircle(float centerX, float centerY, float radius, bool isFilled = true, int lineSegments = 36);
    void drawRectangle(float x, float y, float width, float height, bool isFilled = true);
    
    void drawPolygon(unsigned int renderMode, float* vertices, int vertexSize, int vertexCount);
    void drawPolygon(unsigned int renderMode, float* vertices, int vertexSize, int vertexCount, float* colors, int colorSize);
    
    void drawTexture(OpenGLTexture* texture, float x, float y, float angle = 0.0f);
    void drawTexture(OpenGLTexture* texture, float x, float y, float width, float height, float angle = 0.0f);
    void drawTexture(OpenGLTexture* texture, float* uvCoordinates, float* vertices);
    
private:
    OpenGLRenderer();
    ~OpenGLRenderer();
    
    static OpenGLRenderer* s_Instance;
    OpenGLColor m_BackgroundColor;
    OpenGLColor m_ForegroundColor;
};

#endif
