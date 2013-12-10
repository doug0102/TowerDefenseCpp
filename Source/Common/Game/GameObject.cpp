//
//  GameObject.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-01-09.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "GameObject.h"
#include <stdlib.h>

GameObject::GameObject()
{
  m_Texture = NULL;
  reset();
}

GameObject::~GameObject()
{

}

void GameObject::reset()
{
  setIsActive(true);
}

void GameObject::setPosition(float aX, float aY)
{
  setX(aX);
  setY(aY);
}

void GameObject::setX(float aX)
{
  m_PositionX = aX;
}

void GameObject::setY(float aY)
{
  m_PositionY = aY;
}

void GameObject::getPosition(float &aX, float &aY)
{
  aX = getX();
  aY = getY();
}

float GameObject::getX()
{
  return m_PositionX;
}

float GameObject::getY()
{
  return m_PositionY;
}

void GameObject::setSize(float width, float height)
{
	setWidth(width);
	setHeight(height);
}

void GameObject::setWidth(float width)
{
	m_Width = width;
}

void GameObject::setHeight(float height)
{
	m_Height = height;
}

void GameObject::getSize(float& aWidth, float& aHeight)
{
	aWidth = getWidth();
	aHeight = getHeight();
}

float GameObject::getWidth()
{
	return m_Width;
}

float GameObject::getHeight()
{
	return m_Height;
}

void GameObject::setIsActive(bool aIsActive)
{
  m_IsActive = aIsActive;
}

bool GameObject::getIsActive()
{
  return m_IsActive;
}

OpenGLTexture* GameObject::getTexture()
{
  return m_Texture;
}

