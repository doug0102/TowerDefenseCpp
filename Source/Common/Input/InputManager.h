#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_MAC
#include <Carbon/Carbon.h>
#endif
#elif WIN32
#include <Windows.h>
#endif

#include <map>
#include <vector>

class InputEvent;
class InputListener;

class InputManager
{
public:
    //Static signleton instance methods
    static InputManager* getInstance();
    static void cleanupInstance();
    
    //Methods to register and unregister input events to an InputListener
    void registerListener(InputListener* listener);
    void unregisterListener();
    
    //Mouse event methods
    void handleMouseMovement(float deltaX, float deltaY, float positionX, float positionY);
    void handleMouseLeftClickDown(float positionX, float positionY);
    void handleMouseRightClickDown(float positionX, float positionY);
    void handleMouseLeftClickUp(float positionX, float positionY);
    void handleMouseRightClickUp(float positionX, float positionY);
    
    //Keyboard event methods
    void handleKeyDown(int keyCode);
    void handleKeyUp(int keyCode);
    bool isKeyUp(int keyCode);
    bool isKeyDown(int keyCode);
    
    //Process input events methods
    void processInputEvents();
    
private:
    //Private constructor, deconstructor enforce singleton design pattern
    InputManager();
    ~InputManager();
    
    //Static instance variable
    static InputManager* s_Instance;
    
    //Input listener
    InputListener* m_Listener;
    
    //Input events listener
    std::vector<InputEvent*> m_Events;
};

#endif