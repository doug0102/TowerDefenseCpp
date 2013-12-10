//
//  OpenGLView.m
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2012-12-19.
//  Copyright (c) 2012 Algonquin College. All rights reserved.
//

#import "OpenGLView.h"
#import "ScreenManager.h"
#import "InputManager.h"
#import "OpenGLRenderer.h"
#import <Carbon/Carbon.h>

@interface OpenGLView (InternalMethods)

- (CVReturn)gameLoop:(const CVTimeStamp *)outputTime;
- (void)drawFrame;

@end

@implementation OpenGLView

@synthesize window = m_Window;

static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *now,
                                      const CVTimeStamp *outputTime, CVOptionFlags flagsIn,
                                      CVOptionFlags *flagsOut, void *displayLinkContext)
{
    // go back to Obj-C for easy access to instance variables
    CVReturn result = [(OpenGLView *)displayLinkContext gameLoop:outputTime];
    return result;
}

- (void)dealloc
{
    //Release the display link
    CVDisplayLinkRelease(m_DisplayLink);
    
    //Cleanup the screen manager instance
    ScreenManager::cleanupInstance();
    
    //
    InputManager::cleanupInstance();
    
    //
    m_Window = nil;
    
    [super dealloc];
}

- (id)initWithFrame:(NSRect)frameRect
{
    // context setup
    NSOpenGLPixelFormat *windowedPixelFormat;
    NSOpenGLPixelFormatAttribute attribs[] =
    {
        NSOpenGLPFAWindow,
        NSOpenGLPFAColorSize, 32,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFASingleRenderer,
        0
    };
    
    windowedPixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
    if (windowedPixelFormat == nil)
    {
        NSLog(@"Unable to create windowed pixel format.");
        exit(0);
    }
    self = [super initWithFrame:frameRect pixelFormat:windowedPixelFormat];
    if (self == nil)
    {
        NSLog(@"Unable to create a windowed OpenGL context.");
        exit(0);
    }
    [windowedPixelFormat release];
    
    //Set synch to VBL to eliminate tearing
    GLint vblSynch = 1;
    [[self openGLContext] setValues:&vblSynch forParameter:NSOpenGLCPSwapInterval];
    
    // set up the display link
    CVDisplayLinkCreateWithActiveCGDisplays(&m_DisplayLink);
    CVDisplayLinkSetOutputCallback(m_DisplayLink, MyDisplayLinkCallback, self);
    CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat] CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(m_DisplayLink, cglContext, cglPixelFormat);
    
    return self;
}

- (void)awakeFromNib
{
    //
    NSSize viewBounds = [self bounds].size;
    m_ViewWidth = viewBounds.width;
    m_ViewHeight = viewBounds.height;
    ScreenManager::getInstance()->setScreenSize(m_ViewWidth, m_ViewHeight);
    
    //
    [m_Window setAcceptsMouseMovedEvents:YES];
    
    //Activate the display link
    CVDisplayLinkStart(m_DisplayLink);
}

- (void)reshape
{
    NSSize viewBounds = [self bounds].size;
    m_ViewWidth = viewBounds.width;
    m_ViewHeight = viewBounds.height;
    
    //
    ScreenManager::getInstance()->setScreenSize(m_ViewWidth, m_ViewHeight);
    
    //Sets the size of the OpenGL viewport
    glViewport(0, 0, m_ViewWidth, m_ViewHeight);
    
	//Select the projection stack and apply an orthographic projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, m_ViewWidth, m_ViewHeight, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
    
    //
    NSOpenGLContext    *currentContext = [self openGLContext];
    [currentContext makeCurrentContext];
    
    //Lock the context before we touch it since display link is threaded
    CGLLockContext((CGLContextObj)[currentContext CGLContextObj]);
    
    //Let the context know we've changed size
    [[self openGLContext] update];
    
    //Unlock the context
    CGLUnlockContext((CGLContextObj)[currentContext CGLContextObj]);
}

- (void)drawRect:(NSRect)rect
{
    [self drawFrame];
}

- (CVReturn)gameLoop:(const CVTimeStamp *)outputTime
{
    // deltaTime is unused in this bare bones demo, but here's how to calculate it using display link info
    double deltaTime = 1.0 / (outputTime->rateScalar * (double)outputTime->videoTimeScale / (double)outputTime->videoRefreshPeriod);
    
    //Handle input
    InputManager::getInstance()->processInputEvents();
    
    //Update the game
    ScreenManager::getInstance()->update(deltaTime);
    
    //Draw the current frame
    [self drawFrame];
    
    return kCVReturnSuccess;
}

- (void)drawFrame
{
    //
    NSOpenGLContext *currentContext = [self openGLContext];
    [currentContext makeCurrentContext];
    
    //Must lock GL context because display link is threaded
    CGLLockContext((CGLContextObj)[currentContext CGLContextObj]);
    
    //Clear the OpenGL buffers
    OpenGLRenderer::getInstance()->clear();
    
    //
    ScreenManager::getInstance()->paint();
    
    //
    [currentContext flushBuffer];
    
    //Unlock the GL context, we are done rendering
    CGLUnlockContext((CGLContextObj)[currentContext CGLContextObj]);
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)mouseDown:(NSEvent *)aEvent
{
    if(aEvent != nil)
    {
        NSPoint position = [aEvent locationInWindow];
        position.y = [self bounds].size.height - position.y;
        InputManager::getInstance()->handleMouseLeftClickDown(position.x, position.y);
    }
}

- (void)rightMouseDown:(NSEvent *)aEvent
{
    if(aEvent != nil)
    {
        NSPoint position = [aEvent locationInWindow];
        position.y = [self bounds].size.height - position.y;
        InputManager::getInstance()->handleMouseRightClickDown(position.x, position.y);
    }
}

- (void)mouseUp:(NSEvent *)aEvent
{
    if(aEvent != nil)
    {
        NSPoint position = [aEvent locationInWindow];
        position.y = [self bounds].size.height - position.y;
        InputManager::getInstance()->handleMouseLeftClickUp(position.x, position.y);
    }
}

- (void)rightMouseUp:(NSEvent *)aEvent
{
    if(aEvent != nil)
    {
        NSPoint position = [aEvent locationInWindow];
        position.y = [self bounds].size.height - position.y;
        InputManager::getInstance()->handleMouseRightClickUp(position.x, position.y);
    }
}

- (void)mouseMoved:(NSEvent *)aEvent
{
    if(aEvent != nil)
    {
        //Get the delta of the mouse
        float deltaX = [aEvent deltaX];
        float deltaY = [aEvent deltaY];
        
        //Get the position of the mouse relative to the window in which this view is in
        NSPoint position = [aEvent locationInWindow];
        position.y = [self bounds].size.height - position.y;
        
        //Only fire the mouseMovement event if the mouse is within this view
        if(position.x >= 0.0f && position.x <= m_ViewWidth && position.y >= 0.0f && position.y <= m_ViewHeight)
        {
            InputManager::getInstance()->handleMouseMovement(deltaX, deltaY, position.x, position.y);
        }
    }
}

- (void)mouseDragged:(NSEvent *)aEvent
{
    if(aEvent != nil)
    {
        //Get the delta of the mouse
        float deltaX = [aEvent deltaX];
        float deltaY = [aEvent deltaY];
        
        //Get the position of the mouse relative to the window in which this view is in
        NSPoint position = [aEvent locationInWindow];
        position.y = [self bounds].size.height - position.y;
        
        //Only fire the mouseMovement event if the mouse is within this view
        if(position.x >= 0.0f && position.x <= m_ViewWidth && position.y >= 0.0f && position.y <= m_ViewHeight)
        {
            InputManager::getInstance()->handleMouseMovement(deltaX, deltaY, position.x, position.y);
        }
    }
}

- (void)keyDown:(NSEvent *)aEvent
{
    if(aEvent != nil)
    {
        unsigned short keyCode = [aEvent keyCode];
        InputManager::getInstance()->handleKeyDown(keyCode);
    }
}

- (void)keyUp:(NSEvent *)aEvent
{
    if(aEvent != nil)
    {
        unsigned short keyCode = [aEvent keyCode];
        InputManager::getInstance()->handleKeyUp(keyCode);
    }
}

- (void)flagsChanged:(NSEvent *)aEvent
{
    if(aEvent != nil)
    {
        //Get the keyCode
        unsigned short keyCode = [aEvent keyCode];
        
        //
        if([aEvent modifierFlags] & NSShiftKeyMask)
        {
            InputManager::getInstance()->handleKeyDown(keyCode);
        }
        else if(keyCode == kVK_Shift || keyCode == kVK_RightShift)
        {
            InputManager::getInstance()->handleKeyUp(keyCode);
        }
        
        //
        if([aEvent modifierFlags] & NSControlKeyMask)
        {
            InputManager::getInstance()->handleKeyDown(keyCode);
        }
        else if(keyCode == kVK_Control || keyCode == kVK_RightControl)
        {
            InputManager::getInstance()->handleKeyUp(keyCode);
        }
        
        //
        if([aEvent modifierFlags] & NSAlternateKeyMask)
        {
            InputManager::getInstance()->handleKeyDown(keyCode);
        }
        else if(keyCode == kVK_Option || keyCode == kVK_RightOption)
        {
            InputManager::getInstance()->handleKeyUp(keyCode);
        }
    }
}

@end