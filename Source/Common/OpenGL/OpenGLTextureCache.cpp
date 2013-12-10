//
//  OpenGLTextureCache.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-26.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "OpenGLTextureCache.h"
#include "OpenGLTexture.h"


OpenGLTextureCache* OpenGLTextureCache::m_Instance = NULL;
OpenGLTextureCache* OpenGLTextureCache::getInstance()
{
    if(m_Instance == NULL)
    {
        m_Instance = new OpenGLTextureCache();
    }
    return m_Instance;
}

void OpenGLTextureCache::cleanupInstance()
{
    if(m_Instance != NULL)
    {
        delete m_Instance;
        m_Instance = NULL;
    }
}

OpenGLTextureCache::OpenGLTextureCache()
{

}

OpenGLTextureCache::~OpenGLTextureCache()
{
    for(int i = 0; i < m_TextureCache.size(); i++)
    {
        if(m_TextureCache[i] != NULL)
        {
            delete m_TextureCache[i];
            m_TextureCache[i] = NULL;
        }
    }
    
    m_TextureCache.clear();
}

OpenGLTexture* OpenGLTextureCache::getTexture(const char* filename, const char* atlasKey)
{
    OpenGLTexture* texture = NULL;
    
    for(int i = 0; i < m_TextureCache.size(); i++)
    {
        if(strcmp(m_TextureCache[i]->getFilename().c_str(), filename) == 0)
        {
            if(atlasKey != NULL)
            {
                if(strcmp(m_TextureCache[i]->getAtlasKey().c_str(), atlasKey) == 0)
                {
                    texture = m_TextureCache[i];
                }
            }
            else
            {
                texture = m_TextureCache[i];
            }
        }
    }
    
    //If the texture doesn't exist in the cache, create it
    if(texture == NULL)
    {
        //Create the texture
        texture = new OpenGLTexture(filename, atlasKey);
        
        //Add the texture to the texture cache
        m_TextureCache.push_back(texture);
    }
    
    return texture;
}

