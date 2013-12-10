//
//  OpenGLTexture.h
//  GameDevFramework
//
//  Created by Brad Flood on 11-10-16.
//  Copyright 2011 Algonquin College. All rights reserved.
//

#include "OpenGLTexture.h"
#include "OpenGLTextureManager.h"


OpenGLTextureInfo::OpenGLTextureInfo() :
    sourceX(0),
    sourceY(0),
    sourceWidth(0),
    sourceHeight(0),
    textureWidth(0),
    textureHeight(0),
    textureFormat(0),
    textureId(0),
    textureFilename(""),
    atlasKey("")
{
    
}

OpenGLTextureInfo::OpenGLTextureInfo(const OpenGLTextureInfo& aTextureData) :
    sourceX(aTextureData.sourceX),
    sourceY(aTextureData.sourceY),
    sourceWidth(aTextureData.sourceWidth),
    sourceHeight(aTextureData.sourceHeight),
    textureWidth(aTextureData.textureWidth),
    textureHeight(aTextureData.textureHeight),
    textureFormat(aTextureData.textureFormat),
    textureId(aTextureData.textureId),
    textureFilename(std::string(aTextureData.textureFilename)),
    atlasKey(std::string(aTextureData.textureFilename))
{
    
}



OpenGLTexture::OpenGLTexture(const char* aFilename, const char* aAtlasKey) :
m_TextureInfo(NULL),
m_Color(OpenGLColorWhite()),
m_AnchorX(0.0f),
m_AnchorY(0.0f)
{
    //Safety check that the filename isn't NULL
    if(aFilename != NULL)
    {
        //Allocate the texture info struct
        m_TextureInfo = new OpenGLTextureInfo();
        
        //Set the texture info filename
        m_TextureInfo->textureFilename = std::string(aFilename);
        
        //Load the texture
        if(aAtlasKey != NULL)
        {
            m_TextureInfo->atlasKey = std::string(aAtlasKey);
            OpenGLTextureManager::getInstance()->loadTextureFromAtlas(aFilename, aAtlasKey, &m_TextureInfo);
        }
        else
        {
            OpenGLTextureManager::getInstance()->loadTexture(aFilename, &m_TextureInfo);
        }
    }
}

OpenGLTexture::OpenGLTexture(OpenGLTextureInfo* aTextureInfo) :
m_TextureInfo(NULL),
m_Color(OpenGLColorWhite()),
m_AnchorX(0.0f),
m_AnchorY(0.0f)
{
    //Safety check that the texture info isn't NULL
    if(aTextureInfo != NULL)
    {
        //Allocate the texture info struct
        m_TextureInfo = new OpenGLTextureInfo();
        
        //Copy the texture info data
        m_TextureInfo->sourceX = aTextureInfo->sourceX;
        m_TextureInfo->sourceY = aTextureInfo->sourceY;
        m_TextureInfo->sourceWidth = aTextureInfo->sourceWidth;
        m_TextureInfo->sourceHeight = aTextureInfo->sourceHeight;
        m_TextureInfo->textureWidth = aTextureInfo->textureWidth;
        m_TextureInfo->textureHeight = aTextureInfo->textureHeight;
        m_TextureInfo->textureFormat = aTextureInfo->textureFormat;
        m_TextureInfo->textureId = aTextureInfo->textureId;
        m_TextureInfo->textureFilename = std::string(aTextureInfo->textureFilename);
        m_TextureInfo->atlasKey = std::string(aTextureInfo->atlasKey);
    }
}

OpenGLTexture::~OpenGLTexture()
{
    //Unload the OpenGL texture from memory
    OpenGLTextureManager::getInstance()->unloadTexture(m_TextureInfo);
    
    //Free the texture info struct
    if(m_TextureInfo != NULL)
    {
        delete m_TextureInfo;
        m_TextureInfo = NULL;
    }
}

unsigned int OpenGLTexture::getFormat()
{
    return m_TextureInfo->textureFormat;
}

unsigned int OpenGLTexture::getId()
{
    return m_TextureInfo->textureId;
}

unsigned int OpenGLTexture::getSourceX()
{
    return m_TextureInfo->sourceX;
}

unsigned int OpenGLTexture::getSourceY()
{
    return m_TextureInfo->sourceY;
}

unsigned int OpenGLTexture::getSourceWidth()
{
    return m_TextureInfo->sourceWidth;
}

unsigned int OpenGLTexture::getSourceHeight()
{
    return m_TextureInfo->sourceHeight;
}

unsigned int OpenGLTexture::getTextureWidth()
{
    return m_TextureInfo->textureWidth;
}

unsigned int OpenGLTexture::getTextureHeight()
{
    return m_TextureInfo->textureHeight;
}

std::string OpenGLTexture::getFilename()
{
    return m_TextureInfo->textureFilename;
}

std::string OpenGLTexture::getAtlasKey()
{
    return m_TextureInfo->atlasKey;
}

void OpenGLTexture::setColor(OpenGLColor aColor)
{
    m_Color = aColor;
}

OpenGLColor OpenGLTexture::getColor()
{
    return m_Color;
}

void OpenGLTexture::setAlpha(float aAlpha)
{
    OpenGLColor color = getColor();
    color.alpha = aAlpha;
    setColor(color);
}

float OpenGLTexture::getAlpha()
{
    return getColor().alpha;
}

bool OpenGLTexture::isAnimated()
{
    return false;
}

void OpenGLTexture::setAnchorPoint(float aX, float aY)
{
    m_AnchorX = aX;
    m_AnchorY = aY;
}

float OpenGLTexture::getAnchorPointX()
{
    return m_AnchorX;
}

float OpenGLTexture::getAnchorPointY()
{
    return m_AnchorY;
}

void OpenGLTexture::setTextureInfo(OpenGLTextureInfo* aTextureInfo)
{
    m_TextureInfo = aTextureInfo;
}

OpenGLTextureInfo* OpenGLTexture::getTextureInfo()
{
    return m_TextureInfo;
}
