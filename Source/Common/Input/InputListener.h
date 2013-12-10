#ifndef INPUT_LISTENER_H
#define INPUT_LISTENER_H

class InputListener
{
public:
    virtual void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
    virtual void mouseLeftClickDownEvent(float positionX, float positionY);
    virtual void mouseRightClickDownEvent(float positionX, float positionY);
    virtual void mouseLeftClickUpEvent(float positionX, float positionY);
    virtual void mouseRightClickUpEvent(float positionX, float positionY);
    
    virtual void keyDownEvent(int keyCode);
    virtual void keyUpEvent(int keyCode);
};

#endif