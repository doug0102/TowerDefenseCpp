//
//  InputEvent.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-08-21.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1532_OSX_Game__InputEvent__
#define __GAM_1532_OSX_Game__InputEvent__

#include <stdlib.h>


class InputListener;

enum InputType
{
    KeyboardInput = 0,
    MouseInput,
    UnknownInput
};

class InputEvent
{
public:
    InputEvent();
    virtual ~InputEvent();
    
    virtual InputType getInputType() = 0;
    virtual void processEvent(InputListener* listener) = 0;
};


#endif /* defined(__GAM_1532_OSX_Game__InputEvent__) */
