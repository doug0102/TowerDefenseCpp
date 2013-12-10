//
//  OpenGLAnimatedTexture.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-09-04.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1532_OSX_Game__OpenGLAnimatedTexture__
#define __GAM_1532_OSX_Game__OpenGLAnimatedTexture__

#ifndef OPENGL_ANIMATED_TEXTURE_H
#define OPENGL_ANIMATED_TEXTURE_H

#include "OpenGLTexture.h"


//Animated Texture info struct
class OpenGLAnimatedTextureInfo
{
public:
    OpenGLAnimatedTextureInfo();
    
    OpenGLTextureInfo* textureInfo;
    OpenGLTexture** frames;
    unsigned int frameCount;
    
};

//Callback listener class the animated texture, uses the observer design pattern
class OpenGLAnimatedTexture;
class OpenGLAnimatedTextureListener
{
public:
    virtual void animatedTextureDidFinishAnimating(OpenGLAnimatedTexture* animatedTexture) = 0;
};


//OpenGLAnimatedTexture class, it inherits from OpenGLTexture
class OpenGLAnimatedTexture : public OpenGLTexture
{
public:
    OpenGLAnimatedTexture(const char* filename, bool doesLoop = true, float frameSpeed = 15.0f);
    ~OpenGLAnimatedTexture();
    
    void update(double delta);
    void reset();
    
    void setListener(OpenGLAnimatedTextureListener* listener);
    
    unsigned int getFrameCount();
    
    int getFrameIndex();
    void setFrameIndex(int frameIndex);
    
    bool getDoesLoop();
    void setDoesLoop(bool doesLoop);
    
    bool isAnimated();
    
private:
    OpenGLAnimatedTextureInfo* m_AnimatedTextureInfo;
    OpenGLAnimatedTextureListener* m_Listener;
    
    float m_FrameSpeed;
    double m_ElapsedTime;
    int m_FrameIndex;
    bool m_DoesLoop;
};

#endif

#endif /* defined(__GAM_1532_OSX_Game__OpenGLAnimatedTexture__) */
