//
//  OpenGLTextureManager.cpp
//  GameDevFramework
//
//  Created by Bradley Flood on 12-08-30.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#include "OpenGLTextureManager.h"
#include "OpenGLTextureLoader.h"
#include "../Utils/Utils.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#endif
#elif WIN32
#include <Windows.h>
#include "GL/gl.h"
#endif



OpenGLTextureManager* OpenGLTextureManager::s_Instance = NULL;

OpenGLTextureManager* OpenGLTextureManager::getInstance()
{
    if(s_Instance == NULL)
    {
        s_Instance = new OpenGLTextureManager();
    }
    
    return s_Instance;
}

OpenGLTextureManager::OpenGLTextureManager()
{
    
}

OpenGLTextureManager::~OpenGLTextureManager()
{
    
}

void OpenGLTextureManager::loadTexture(const std::string& aFilename, OpenGLTextureInfo** aTextureInfo)
{
    //Find the filename in the map
    std::map<std::string, TextureIdRetainInfo, compareFilenames>::iterator textureIdRetainIterator;
    textureIdRetainIterator = m_TextureIdRetainMap.find(aFilename);
    
    //Does the filename already exist in our map
    bool doesFilenameExist = textureIdRetainIterator != m_TextureIdRetainMap.end();
    if(doesFilenameExist == true)
    {
        //Setup the texture info
        TextureIdRetainInfo textureIdRetainInfo = (*textureIdRetainIterator).second;
        
        //Increment the retain count
        OpenGLTextureInfo* textureInfo = *aTextureInfo;
        textureInfo->textureId = textureIdRetainInfo.textureId;
        textureIdRetainInfo.retainCount++;
        m_TextureIdRetainMap[aFilename] = textureIdRetainInfo;
    }
    
    //Get the path for the png file from the resource manager
    std::string pngPath = ResourceUtils::getPathForResource(aFilename.c_str(), "png");
    
    //Load the texture from the png path
    OpenGLTextureLoader::loadTextureFromPath(pngPath.c_str(), aTextureInfo);
    
    //If the texture info was not found we need to add it to the map
    if(doesFilenameExist == false)
    {
        //Load the texture data
        TextureIdRetainInfo textureIdRetainInfo;
        
        //Set the texture info id and set the retain count to 1
        OpenGLTextureInfo* textureInfo = *aTextureInfo;
        textureIdRetainInfo.textureId = textureInfo->textureId;
        textureIdRetainInfo.retainCount = 1;
        m_TextureIdRetainMap[aFilename] = textureIdRetainInfo;
    }
}

void OpenGLTextureManager::loadTextureFromAtlas(const std::string& aFilename, const std::string& aAtlasKey, OpenGLTextureInfo** aTextureInfo)
{
    //Find the filename in the map
    std::map<std::string, TextureIdRetainInfo, compareFilenames>::iterator textureIdRetainIterator;
    textureIdRetainIterator = m_TextureIdRetainMap.find(aFilename);
    
    //Does the filename already exist in our map
    bool doesFilenameExist = textureIdRetainIterator != m_TextureIdRetainMap.end();
    if(doesFilenameExist == true)
    {
        //Setup the texture info
        TextureIdRetainInfo textureIdRetainInfo = (*textureIdRetainIterator).second;
        
        //Increment the retain count
        OpenGLTextureInfo* textureInfo = *aTextureInfo;
        textureInfo->textureId = textureIdRetainInfo.textureId;
        textureIdRetainInfo.retainCount++;
        m_TextureIdRetainMap[aFilename] = textureIdRetainInfo;
    }
    
    //Get the path for the png file from the resource manager
    std::string pngPath = ResourceUtils::getPathForResource(aFilename.c_str(), "png");
    std::string jsonPath = ResourceUtils::getPathForResource(aFilename.c_str(), "json");
    
    //Load the texture from the png path
    OpenGLTextureLoader::loadTextureFromAtlas(pngPath.c_str(), jsonPath.c_str(), aAtlasKey.c_str(), aTextureInfo);
    
    //If the texture info was not found we need to add it to the map
    if(doesFilenameExist == false)
    {
        //Load the texture data
        TextureIdRetainInfo textureIdRetainInfo;
        
        //Set the texture info id and set the retain count to 1
        OpenGLTextureInfo* textureInfo = *aTextureInfo;
        textureIdRetainInfo.textureId = textureInfo->textureId;
        textureIdRetainInfo.retainCount = 1;
        m_TextureIdRetainMap[aFilename] = textureIdRetainInfo;
    }
}

void OpenGLTextureManager::loadAnimatedTexture(const std::string& aFilename, OpenGLAnimatedTextureInfo** aAnimatedTextureInfo)
{
    //Find the filename in the map
    std::map<std::string, TextureIdRetainInfo, compareFilenames>::iterator textureIdRetainIterator;
    textureIdRetainIterator = m_TextureIdRetainMap.find(aFilename);
    
    //Does the filename already exist in our map
    bool doesFilenameExist = textureIdRetainIterator != m_TextureIdRetainMap.end();
    if(doesFilenameExist == true)
    {
        //Setup the texture info
        TextureIdRetainInfo textureIdRetainInfo = (*textureIdRetainIterator).second;
        
        //Increment the retain count
        OpenGLAnimatedTextureInfo* animatedTextureInfo = *aAnimatedTextureInfo;
        animatedTextureInfo->textureInfo->textureId = textureIdRetainInfo.textureId;
        textureIdRetainInfo.retainCount++;
        m_TextureIdRetainMap[aFilename] = textureIdRetainInfo;
    }
    
    //Get the path for the png file from the resource manager
    std::string pngPath = ResourceUtils::getPathForResource(aFilename.c_str(), "png");
    std::string jsonPath = ResourceUtils::getPathForResource(aFilename.c_str(), "json");
    
    //Load the texture from the png path
    OpenGLTextureLoader::loadAnimatedTextureFromPath(pngPath.c_str(), jsonPath.c_str(), aAnimatedTextureInfo);
    
    //If the texture info was not found we need to add it to the map
    if(doesFilenameExist == false)
    {
        //Load the texture data
        TextureIdRetainInfo textureIdRetainInfo;
        
        //Set the texture info id and set the retain count to 1
        OpenGLAnimatedTextureInfo* animatedTextureInfo = *aAnimatedTextureInfo;
        textureIdRetainInfo.textureId = animatedTextureInfo->textureInfo->textureId;
        textureIdRetainInfo.retainCount = 1;
        m_TextureIdRetainMap[aFilename] = textureIdRetainInfo;
    }
}

void OpenGLTextureManager::unloadTexture(OpenGLTextureInfo* aTextureInfo)
{
    if(aTextureInfo != NULL)
    {
        if(aTextureInfo->textureFilename == "")
        {
            glDeleteTextures(1, &aTextureInfo->textureId);
            return;
        }
        
        //Find the filename in the map
        std::map<std::string, TextureIdRetainInfo, compareFilenames>::iterator textureIdRetainIterator;
        textureIdRetainIterator = m_TextureIdRetainMap.find(aTextureInfo->textureFilename);
        
        bool unloadTexture = false;
        
        //Does the filename already exist in our map
        if(textureIdRetainIterator != m_TextureIdRetainMap.end())
        {
            //Setup the texture info
            TextureIdRetainInfo textureIdRetainInfo = (*textureIdRetainIterator).second;
            
            //Decrement the retain count
            textureIdRetainInfo.retainCount--;
            
            //If we hit zero, set the unloadTexture flag to true
            if(textureIdRetainInfo.retainCount == 0)
            {
                unloadTexture = true;
            }
            
            //Update the retain map
            m_TextureIdRetainMap[aTextureInfo->textureFilename] = textureIdRetainInfo;
        }
        
        //If the retain count hit 0, unload the texture, and erase the filename from the retain map
        if(unloadTexture == true)
        {
            m_TextureIdRetainMap.erase(aTextureInfo->textureFilename);
            glDeleteTextures(1, &aTextureInfo->textureId);
        }
    }
}

void OpenGLTextureManager::unloadAnimatedTexture(OpenGLAnimatedTextureInfo* aAnimatedTextureInfo)
{
    if(aAnimatedTextureInfo != NULL)
    {
        unloadTexture(aAnimatedTextureInfo->textureInfo);
    }
}

