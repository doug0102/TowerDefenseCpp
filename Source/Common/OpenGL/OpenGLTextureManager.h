//
//  OpenGLTextureManager.h
//  GameDevFramework
//
//  Created by Bradley Flood on 12-08-30.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#ifndef OPENGL_TEXTURE_MANAGER_H
#define OPENGL_TEXTURE_MANAGER_H

#include "OpenGLTexture.h"
#include "OpenGLAnimatedTexture.h"
#include <map>
#include <string>


class OpenGLTextureManager
{
public:
    static OpenGLTextureManager* getInstance();
    
    void loadTexture(const std::string& filename, OpenGLTextureInfo** textureInfo);
    void loadTextureFromAtlas(const std::string& filename, const std::string& atlasKey, OpenGLTextureInfo** textureInfo);
    void loadAnimatedTexture(const std::string& filename, OpenGLAnimatedTextureInfo** animatedTextureInfo);
    
    void unloadTexture(OpenGLTextureInfo* textureInfo);
    void unloadAnimatedTexture(OpenGLAnimatedTextureInfo* animatedTextureInfo);
    
private:
    OpenGLTextureManager();
    ~OpenGLTextureManager();
    
    //Singleton instance of OpenGLTextureManager
    static OpenGLTextureManager* s_Instance;
    
    //Private struct to keep track of the OpenGL id and its retain count.
    typedef struct TextureIdRetainInfo
    {
        unsigned int textureId;
        int retainCount;
    }TextureIdRetainInfo;
    
    //Compare filenames function for the texture retain map
    struct compareFilenames
    {
        bool operator()(const std::string& filenameA, const std::string& filenameB)
        {
            return std::strcmp(filenameA.c_str(), filenameB.c_str()) < 0;
        }
    };
    
    //Map to keep track of the OpenGL texture's loaded into memory, this prevents us from loading the same texture into memory twice
    std::map<std::string, TextureIdRetainInfo, compareFilenames> m_TextureIdRetainMap;
};

#endif
