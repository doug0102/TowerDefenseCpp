//
//  MouseEvent.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-08-21.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1532_OSX_Game__MouseEvent__
#define __GAM_1532_OSX_Game__MouseEvent__

#include "InputEvent.h"


class InputListener;

class MouseEvent : public InputEvent
{
public:
    //Mouse event types
    enum MouseInputType
    {
        MouseMovementInput = 0,
        MouseLeftClickDownInput,
        MouseLeftClickUpInput,
        MouseRightClickDownInput,
        MouseRightClickUpInput,
        MouseUnknownInput
    };
    
    MouseEvent(MouseInputType mouseInput, float positionX, float positionY, float deltaX = 0.0f, float deltaY = 0.0f);
    ~MouseEvent();
    
    InputType getInputType();
    void processEvent(InputListener* listener);
    
private:
    MouseInputType m_InputType;
    float m_PositionX;
    float m_PositionY;
    float m_DeltaX;
    float m_DeltaY;
};

#endif /* defined(__GAM_1532_OSX_Game__MouseEvent__) */
