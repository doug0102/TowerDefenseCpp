#include "InputManager.h"
#include "InputListener.h"
#include "InputEvent.h"
#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include <stdlib.h>


InputManager* InputManager::s_Instance = NULL;
InputManager* InputManager::getInstance()
{
	if(s_Instance == NULL)
	{
		s_Instance = new InputManager();
	}
	
	return s_Instance;
}

void InputManager::cleanupInstance()
{
	if(s_Instance != NULL)
	{
		delete s_Instance;
		s_Instance = NULL;
	}
}

InputManager::InputManager()
{
    m_Listener = NULL;
}

InputManager::~InputManager()
{
    m_Listener = NULL;
    
    while (m_Events.size() > 0)
    {
        InputEvent* event = m_Events.back();
        delete event;
        m_Events.pop_back();
    }
}

void InputManager::registerListener(InputListener* aListener)
{
    m_Listener = aListener;
}

void InputManager::unregisterListener()
{
    m_Listener = NULL;
}

bool InputManager::isKeyUp(int aKeyCode)
{
#if WIN32
	if((GetKeyState(aKeyCode) & 0x8000) == 0)
	{
		return true;
	}
#elif TARGET_OS_MAC
    CGEventSourceStateID eventSource = kCGEventSourceStateCombinedSessionState;
    if(CGEventSourceKeyState(eventSource, aKeyCode) == true)
    {
        return true;
    }
#endif
    
	return false;
}

bool InputManager::isKeyDown(int aKeyCode)
{
#if WIN32
	if((GetKeyState(aKeyCode) & 0x8000) > 0)
	{
		return true;
	}
#elif TARGET_OS_MAC
    CGEventSourceStateID eventSource = kCGEventSourceStateCombinedSessionState;
    if(CGEventSourceKeyState(eventSource, aKeyCode) == true)
    {
        return true;
    }
#endif
    
	return false;
}

void InputManager::processInputEvents()
{
    while (m_Events.size() > 0)
    {
        //Process the input event
        InputEvent* event = m_Events.front();
        event->processEvent(m_Listener);
        
        //Get rid of the input event it is no longer needed
        delete event;
        m_Events.erase(m_Events.begin());
    }
}

void InputManager::handleMouseMovement(float aDeltaX, float aDeltaY, float aPositionX, float aPositionY)
{
    m_Events.push_back(new MouseEvent(MouseEvent::MouseMovementInput, aPositionX, aPositionY, aDeltaX, aDeltaY));
}

void InputManager::handleMouseLeftClickDown(float aPositionX, float aPositionY)
{
    m_Events.push_back(new MouseEvent(MouseEvent::MouseLeftClickDownInput, aPositionX, aPositionY));
}

void InputManager::handleMouseRightClickDown(float aPositionX, float aPositionY)
{
    m_Events.push_back(new MouseEvent(MouseEvent::MouseRightClickDownInput, aPositionX, aPositionY));
}

void InputManager::handleMouseLeftClickUp(float aPositionX, float aPositionY)
{
    m_Events.push_back(new MouseEvent(MouseEvent::MouseLeftClickUpInput, aPositionX, aPositionY));
}

void InputManager::handleMouseRightClickUp(float aPositionX, float aPositionY)
{
    m_Events.push_back(new MouseEvent(MouseEvent::MouseRightClickUpInput, aPositionX, aPositionY));
}

void InputManager::handleKeyDown(int aKeyCode)
{
    m_Events.push_back(new KeyboardEvent(KeyboardEvent::KeyDownInput, aKeyCode));
}

void InputManager::handleKeyUp(int aKeyCode)
{
    m_Events.push_back(new KeyboardEvent(KeyboardEvent::KeyUpInput, aKeyCode));
}
