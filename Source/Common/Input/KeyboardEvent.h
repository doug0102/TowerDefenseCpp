//
//  KeyboardEvent.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-08-21.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1532_OSX_Game__KeyboardEvent__
#define __GAM_1532_OSX_Game__KeyboardEvent__

#include "InputEvent.h"


class KeyboardEvent : public InputEvent
{
public:
    //Keyboard input types
    enum KeyboardInputType
    {
        KeyUpInput = 0,
        KeyDownInput,
        KeyUnknownInput
    };
    
    
    KeyboardEvent(KeyboardInputType keyboardInput, int keyCode);
    ~KeyboardEvent();
    
    InputType getInputType();
    void processEvent(InputListener* listener);
    
private:
    KeyboardInputType m_InputType;
    int m_KeyCode;
};

#endif /* defined(__GAM_1532_OSX_Game__KeyboardEvent__) */
