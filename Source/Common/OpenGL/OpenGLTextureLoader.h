//
//  OpenGLTextureLoader.h
//  GameDevFramework
//
//  Created by Bradley Flood on 12-08-30.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#ifndef OPENGL_TEXTURE_LOADER_H
#define OPENGL_TEXTURE_LOADER_H

#include "OpenGLTexture.h"
#include "OpenGLAnimatedTexture.h"
#include "../Libraries/libpng/png.h"


namespace OpenGLTextureLoader
{
    bool loadTextureFromPath(const char* path, OpenGLTextureInfo** textureInfo);
    bool loadTextureFromAtlas(const char* pngPath, const char* jsonPath, const char* atlasKey, OpenGLTextureInfo** textureInfo);
    bool loadAnimatedTextureFromPath(const char* pngPath, const char* jsonPath, OpenGLAnimatedTextureInfo** animatedTextureInfo);
    
    void setTextureFromData(png_structp png_ptr, png_infop info_ptr, OpenGLTextureInfo** textureInfo);
}

#endif
