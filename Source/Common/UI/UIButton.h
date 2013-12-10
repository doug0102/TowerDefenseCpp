//
//  UIButton.h
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-10-09.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__UIButton__
#define __GAM_1514_OSX_Game__UIButton__

#include <stdlib.h>


class OpenGLTexture;
class UIButtonListener;

class UIButton
{
public:
    UIButton(const char* textureFile, const char* overlayFile = NULL);
    virtual ~UIButton();
    
    virtual void paint();
    
    virtual void mouseMovementEvent(float positionX, float positionY);
    virtual void mouseLeftClickUpEvent(float positionX, float positionY);
    
    virtual void keyUpEvent(int keyCode);
    
    virtual void setListener(UIButtonListener* listener);
    virtual void setCenterPosition(float centerX, float centerY);
    virtual void setCenterX(float centerX);
    virtual void setCenterY(float centerY);
    virtual void setIsSelected(bool isSelected);
    
    virtual void swapOverlay(const char* overlayFile);
    
    virtual float getWidth();
    virtual float getHeight();

	// Changes the texture of the button
	virtual void changeButtonTexture(const char* textureFile);
    
protected:
	friend class SettingsMenu;

    UIButtonListener* m_Listener;
    OpenGLTexture* m_NormalState;
    OpenGLTexture* m_SelectedState;
    OpenGLTexture* m_Overlay;
    float m_CenterPositionX;
    float m_CenterPositionY;
    bool m_IsSelected;
};


class UIButtonListener
{
public:
    virtual void buttonAction(UIButton* button) = 0;
    virtual void buttonIsSelected(UIButton* button) = 0;
    virtual bool buttonShouldBeDeselectedOnExit(UIButton* button) { return false; }
};

#endif /* defined(__GAM_1514_OSX_Game__UIButton__) */







