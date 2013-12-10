//
//  MouseEvent.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-08-21.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "MouseEvent.h"
#include "InputListener.h"


MouseEvent::MouseEvent(MouseInputType aMouseInput, float aPositionX, float aPositionY, float aDeltaX, float aDeltaY) :
    m_InputType(aMouseInput),
    m_PositionX(aPositionX),
    m_PositionY(aPositionY),
    m_DeltaX(aDeltaX),
    m_DeltaY(aDeltaY)
{
    
}

MouseEvent::~MouseEvent()
{
    
}

InputType MouseEvent::getInputType()
{
    return MouseInput;
}

void MouseEvent::processEvent(InputListener* aListener)
{
    if(aListener != NULL)
    {
        switch (m_InputType)
        {
            case MouseMovementInput:
                aListener->mouseMovementEvent(m_DeltaX, m_DeltaY, m_PositionX, m_PositionY);
                break;
                
            case MouseLeftClickDownInput:
                aListener->mouseLeftClickDownEvent(m_PositionX, m_PositionY);
                break;
                
            case MouseLeftClickUpInput:
                aListener->mouseLeftClickUpEvent(m_PositionX, m_PositionY);
                break;
                
            case MouseRightClickDownInput:
                aListener->mouseRightClickDownEvent(m_PositionX, m_PositionY);
                break;
                
            case MouseRightClickUpInput:
                aListener->mouseRightClickUpEvent(m_PositionX, m_PositionY);
                break;
                
            default:
                break;
        }
    }
}
