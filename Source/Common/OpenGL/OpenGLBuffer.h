//
//  OpenGLBuffer.h
//  GameDevFramework
//
//  Created by Brad Flood on 11-10-16.
//  Copyright 2011 Algonquin College. All rights reserved.
//

#ifndef OPENGL_BUFFER_H
#define OPENGL_BUFFER_H

typedef struct OpenGLBuffer
{
	GLuint viewFramebuffer;
	GLuint viewRenderbuffer;
    GLuint depthRenderbuffer;
	GLint bufferWidth;
	GLint bufferHeight;
}OpenGLBuffer;

#endif
