//
//  OpenGLView.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2012-12-19.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGL/OpenGL.h>


@interface OpenGLView : NSOpenGLView
{
    NSWindow *m_Window;
    CVDisplayLinkRef m_DisplayLink;
    float m_ViewWidth;
    float m_ViewHeight;
}

@property (nonatomic, assign) IBOutlet NSWindow *window;

@end
