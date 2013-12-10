#ifndef SCREEN_H
#define SCREEN_H

#include "../Input/Input.h"

//All game screens will inherit from Screen to
//ensure they have the functionality needed by
//the ScreenManager. Screen inherits from Input Listener,
//override the input methods to gain input functionality.
class Screen : public InputListener
{
public:
    Screen();
    virtual ~Screen();
    
    //Pure virtual getName method, used to identify each screen
    virtual const char* getName() = 0;
    
    //Pure virtual update and paint lifecycle methods, these
    //methods must be implement in inheriting classes.
    virtual void update(double delta) = 0;
    virtual void paint() = 0;
    
    //Reset lifecycle method, can be overridden
    virtual void reset();
    
    //Screen appearance event methods, can be overridden
    virtual void screenWillAppear();
    virtual void screenWillDisappear();
    
    //Mouse event methods, can be overridden
    virtual void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    virtual void mouseLeftClickDownEvent(float positionX, float positionY);
    virtual void mouseRightClickDownEvent(float positionX, float positionY);
    virtual void mouseLeftClickUpEvent(float positionX, float positionY);
    virtual void mouseRightClickUpEvent(float positionX, float positionY);
    
    //Key up and down event methods, can be overridden
    virtual void keyDownEvent(int keyCode);
    virtual void keyUpEvent(int keyCode);
    
    //Conveniance methods to access the screen's width and height
    float getWidth();
    float getHeight();
};

#endif