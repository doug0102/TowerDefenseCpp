//
//  ResourceUtilsObjC.h
//  GameDevFramework
//
//  Created by Bradley Flood on 12-08-30.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#ifndef RESOURCE_UTILS_OBJC_H
#define RESOURCE_UTILS_OBJC_H

#include <string>

namespace ResourceUtilsObjC
{
    std::string getPathForResource(const char* fileName, const char* fileType);
}

#endif