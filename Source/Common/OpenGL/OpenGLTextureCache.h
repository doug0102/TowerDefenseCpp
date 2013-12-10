//
//  OpenGLTextureCache.h
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-26.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__OpenGLTextureCache__
#define __GAM_1514_OSX_Game__OpenGLTextureCache__

#include <stdlib.h>
#include <vector>


class OpenGLTexture;

class OpenGLTextureCache
{
public:
    static OpenGLTextureCache* getInstance();
    static void cleanupInstance();
    
    OpenGLTexture* getTexture(const char* filename, const char* atlasKey = NULL);

private:
    OpenGLTextureCache();
    ~OpenGLTextureCache();
    
    static OpenGLTextureCache* m_Instance;
    std::vector<OpenGLTexture*> m_TextureCache;
};

#endif /* defined(__GAM_1514_OSX_Game__OpenGLTextureCache__) */
