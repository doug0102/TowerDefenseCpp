#include "Screen.h"
#include "ScreenManager.h"


Screen::Screen()
{
    
}

Screen::~Screen()
{
    
}

void Screen::reset()
{
    
}

void Screen::screenWillAppear()
{
    
}

void Screen::screenWillDisappear()
{
    
}

void Screen::mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY)
{
    
}

void Screen::mouseLeftClickDownEvent(float positionX, float positionY)
{
    
}

void Screen::mouseRightClickDownEvent(float positionX, float positionY)
{
    
}

void Screen::mouseLeftClickUpEvent(float positionX, float positionY)
{
    
}

void Screen::mouseRightClickUpEvent(float positionX, float positionY)
{
    
}

void Screen::keyDownEvent(int keyCode)
{
    
}

void Screen::keyUpEvent(int keyCode)
{
    
}

float Screen::getWidth()
{
    return ScreenManager::getInstance()->getScreenWidth();
}

float Screen::getHeight()
{
    return ScreenManager::getInstance()->getScreenHeight();
}


