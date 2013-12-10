//
//  KeyboardEvent.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-08-21.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "KeyboardEvent.h"
#include "InputListener.h"


KeyboardEvent::KeyboardEvent(KeyboardInputType aKeyboardInput, int aKeyCode) :
    m_InputType(aKeyboardInput),
    m_KeyCode(aKeyCode)
{
    
}

KeyboardEvent::~KeyboardEvent()
{
    
}

InputType KeyboardEvent::getInputType()
{
    return KeyboardInput;
}

void KeyboardEvent::processEvent(InputListener* aListener)
{
    if(aListener != NULL)
    {
        switch (m_InputType)
        {
            case KeyUpInput:
                aListener->keyUpEvent(m_KeyCode);
                break;
                
            case KeyDownInput:
                aListener->keyDownEvent(m_KeyCode);
                break;
                
            default:
                break;
        }
    }
}