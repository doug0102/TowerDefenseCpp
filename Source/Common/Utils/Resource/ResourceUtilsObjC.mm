//
//  ResourceUtilsObjC.m
//  GameDevFramework
//
//  Created by Bradley Flood on 12-08-30.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#import "ResourceUtilsObjC.h"


namespace ResourceUtilsObjC
{
    std::string getPathForResource(const char* aFileName, const char* aFileType)
    {
        @autoreleasepool
        {
            NSString* path = [[NSString alloc] initWithCString:aFileName encoding:NSUTF8StringEncoding];
            NSString* type = [[NSString alloc] initWithCString:aFileType encoding:NSUTF8StringEncoding];
            NSString* fullPath = [[NSBundle mainBundle] pathForResource:path ofType:type inDirectory:@"Resources"];
            [path release];
            [type release];
            
            //Safety check the path
            if(fullPath != nil)
            {
                return std::string([fullPath UTF8String]);
            }
            
            return "";
        }
    }
}

