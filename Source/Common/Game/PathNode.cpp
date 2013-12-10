//
//  PathNode.cpp
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-11-13.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "PathNode.h"
#include "Tiles/Tile.h"
#include <stdlib.h>


PathNode::PathNode(Tile* tile) :
    m_Tile(tile),
    m_ScoreG(0),
    m_ScoreH(0),
    m_ParentNode(NULL)
{

}

PathNode::~PathNode()
{
    m_Tile = NULL;
    m_ParentNode = NULL;
}

void PathNode::paintScore(OpenGLColor color)
{
    if(m_Tile != NULL)
    {
        if(getScoreF() != 0)
        {
            m_Tile->paintScore(color, getScoreG(), getScoreH(), getScoreF());
        }
    }
}

Tile* PathNode::getTile()
{
    return m_Tile;
}

int PathNode::getScoreG()
{
    return m_ScoreG;
}

int PathNode::getScoreH()
{
    return m_ScoreH;
}

int PathNode::getScoreF()
{
    return getScoreG()+ getScoreH();
}

PathNode* PathNode::getParentNode()
{
    return m_ParentNode;
}

void PathNode::setScoreG(int scoreG)
{
    m_ScoreG = scoreG;
}

void PathNode::setScoreH(int scoreH)
{
    m_ScoreH = scoreH;
}

void PathNode::setParentNode(PathNode* parentNode)
{
    m_ParentNode = parentNode;
}

bool PathNode::compareNodes(PathNode* nodeA, PathNode* nodeB)
{
    return nodeA->getScoreF() < nodeB->getScoreF();
}