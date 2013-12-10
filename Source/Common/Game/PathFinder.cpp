//
//  PathFinder.cpp
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#include "PathFinder.h"
#include "PathNode.h"
#include "Level.h"
#include "Tiles/Tile.h"
#include "../Constants/Constants.h"
#include <stdlib.h>
#include <algorithm>
#include <math.h>



PathFinder::PathFinder(Level* level, PathFinderListener* listener) :
    m_Level(level),
    m_Listener(listener),
    m_State(StateIdle),
    m_DestinationTileIndex(-1),
    m_SearchDelay(0.0),
    m_EnableSearchDelay(false)
{

}

PathFinder::~PathFinder()
{
    clearPathNodes();
}

void PathFinder::findPath(Tile* aCurrentTile, Tile* aDestinationTile)
{
    //safety check that the state is idle, if it isnt then a path is either already found and in the process of being found

	if(m_State != StateIdle)
	{
		return;
	}

	// Cycle through and reset all the tile path flags to false
	for(int i = 0; i < m_Level->getNumberOfTiles(); i++)
	{
		Tile* tile = m_Level->getTileForIndex(i);
		if(tile != NULL && tile->isWalkableTile() == true)
		{
			tile->setIsPath(false);
		}
	}

	// Clear the path nodes
	clearPathNodes();

	// Get the current tile and destination tile indexes
	int currentTileIndex = m_Level->getTileIndexForTile(aCurrentTile);
	m_DestinationTileIndex = m_Level->getTileIndexForTile(aDestinationTile);

	//Safety check that the destination tile and the current tile endexes arent the same
	if(currentTileIndex == m_DestinationTileIndex)
	{
		return;
	}

	// Make sure the destination tile is walkable
	if(aDestinationTile->isWalkableTile() == false)
	{
		return;
	}

	// Allocate the current tile's path node and add it to the open list
	PathNode* pathNode = new PathNode(aCurrentTile);
	addPathNodeToOpenList(pathNode);

	//set the state to searching
	m_State = StateSearchingPath;

	//Set the search delay to zero
	m_SearchDelay = 0.0;
}

void PathFinder::update(double aDelta)
{
	if(m_SearchDelay > 0.0)
	{
		m_SearchDelay -= aDelta;
		if(m_SearchDelay <= 0.0)
		{
			m_SearchDelay = 0.0;
		}
		return;
	}


	// Is the state searching? (switched from the IF statement)
	while(isSearchingPath() == true && m_DestinationTileIndex != 1)
	{
		// Safety check that there is actually something in the open list
		if(m_PathNodeOpen.size() == 0)
		{
			//Set the state to error
			m_State = StateError;

			// Notify the listener
			if(m_Listener != NULL)
			{
				m_Listener->pathFinderFinishedSearching(this, false);
			}

			return;
		}

		//Get the  node with the lowest F score from the open list, since this is sorted
		//it should be the first element in the open list.
		PathNode* currentNode = m_PathNodeOpen.front();

		// Add the node to the closed list and remove it from the open list
		m_PathNodeClosed.push_back(currentNode);
		m_PathNodeOpen.erase(m_PathNodeOpen.begin());

		// Check to see if the node is at the destination tile
		int currentNodeTileIndex = m_Level->getTileIndexForTile(currentNode->getTile());
		if(currentNodeTileIndex == m_DestinationTileIndex)
		{
			// Build the final node path, this will use the current nodes parent to track
			// through the pth nodes all th way to the start
			buildFinalNodePath(currentNode);

			// Set the state to path found
			m_State = StateFoundPath;

			// Notify the listener
			if(m_Listener != NULL)
			{
				m_Listener->pathFinderFinishedSearching(this, true);
			}

			return;
		}

		// If we got here that means we haven't reached our destination
		// We need to get the adjacent tiles from the node and add them to the
		// open list
		std::vector<Tile*> adjacentTiles;

		// Check the tile above, is it walkable
		addAdjacentTile(adjacentTiles, currentNode->getTile(), 0, -1);

		// Check the tile below, is it walkable
		addAdjacentTile(adjacentTiles, currentNode->getTile(), 0, 1);

		// Check the tile to the left, is it walkable
		addAdjacentTile(adjacentTiles, currentNode->getTile(), -1, 0);

		// Check the tile to the right, is it walkable
		addAdjacentTile(adjacentTiles, currentNode->getTile(), 1, 0);

		// Cycle through the adjacent tiles that are walkable
		for(int i = 0; i < adjacentTiles.size(); i++)
		{
			Tile* adjacentTile = adjacentTiles.at(i);

			// Does the tile exist in the closed list
			if(doesTileExistInClosedList(adjacentTile) == true)
			{
				// If it does disregard it
				continue;
			}

			// Does the tile exist in the open list
			if(doesTileExistInOpenList(adjacentTile) == false)
			{
				// If it doesn't create a new node for the tile
				PathNode* adjacentNode = new PathNode(adjacentTile);

				// Set the parent node
				adjacentNode->setParentNode(currentNode);

				// Calculate the G score
				adjacentNode->setScoreG(currentNode->getScoreG() + 1);

				// Calculate the H score
				Tile* destinationTile = m_Level->getTileForIndex(m_DestinationTileIndex);
				int scoreH = getManhattanDistanceCost(adjacentTile, destinationTile);
				adjacentNode->setScoreH(scoreH);

				// Add the tile to the Open List and sort it
				addPathNodeToOpenList(adjacentNode);
			}
			else
			{
				// if it does exist in the open list compare the scores and keep one with
				// the lowest F score, which really means keep the one with the lowest G score,
				// since the H score will be identical
				PathNode* existingNode = getOpenPathNodeForTile(adjacentTile);

				// if the tile has a lower F score, update the G score and upadte the parent node
				if(currentNode->getScoreG() + 1 < existingNode->getScoreG())
				{
					// Update the G score and update the parent node
					existingNode->setScoreG(currentNode->getScoreG() + 1);
					existingNode->setParentNode(currentNode);

					// Re-sort the open list
					sortOpenList();
				}
			}
		}
	}
    
    
    //If the search delay is enabled, set the delay timer
    if(m_EnableSearchDelay == true)
    {
        m_SearchDelay = PATH_FINDING_DELAY;
    }
}

void PathFinder::paint()
{
    //Paint the open list path scoring
    for(int i = 0; i < m_PathNodeOpen.size(); i++)
    {
        m_PathNodeOpen.at(i)->paintScore(OpenGLColorRed());
    }
    
    //Paint the closed list path scoring
    for(int i = 0; i < m_PathNodeClosed.size(); i++)
    {
        m_PathNodeClosed.at(i)->paintScore(OpenGLColorBlue());
    }
    
    //Paint the final path scoring
    for(int i = 0; i < m_PathNodeFinal.size(); i++)
    {
        m_PathNodeFinal.at(i)->paintScore(OpenGLColorYellow());
    }
}

void PathFinder::reset()
{
    m_State = StateIdle;
}

void PathFinder::addAdjacentTile(std::vector<Tile*>& aAdjacentTiles, Tile* aCurrentTile, int aDeltaX, int aDeltaY)
{
	int adjacentCoordinateX = m_Level->getTileCoordinateForPosition(aCurrentTile->getX()) + aDeltaX;
	int adjacentCoordinateY = m_Level->getTileCoordinateForPosition(aCurrentTile->getY()) + aDeltaY;

	Tile* adjacentTile = m_Level->getTileForCoordinates(adjacentCoordinateX, adjacentCoordinateY);
	if(adjacentTile != NULL)
	{
		// Is the tile walkable and valid (ie not outside the bounds of the level)
		bool isWalkable = adjacentTile->isWalkableTile();
		bool isValid = m_Level->validateTileCoordinates(adjacentCoordinateX, adjacentCoordinateY);

		if(isWalkable == true && isValid == true)
		{
			aAdjacentTiles.push_back(adjacentTile);
		}

	}
}

bool PathFinder::doesTileExistInClosedList(Tile* aTile)
{
    //Get the tile index from the level for the tile pointer
    int tileIndex = m_Level->getTileIndexForTile(aTile);
    
    //Cycle through the closed list and compare the tile indexes
    for(int i = 0; i < m_PathNodeClosed.size(); i++)
    {
        PathNode* pathNode = m_PathNodeClosed.at(i);
        if(m_Level->getTileIndexForTile(pathNode->getTile()) == tileIndex)
        {
            return true;
        }
    }
    
    //The tile doesn't exist in the closed list
    return false;
}

bool PathFinder::doesTileExistInOpenList(Tile* aTile)
{
    return getOpenPathNodeForTile(aTile) != NULL;
}

PathNode* PathFinder::getOpenPathNodeForTile(Tile* aTile)
{
    //Get the tile index from the level for the tile pointer
    int tileIndex = m_Level->getTileIndexForTile(aTile);
    
    //Cycle through the open list and compare the tile indexes
    for(int i = 0; i < m_PathNodeOpen.size(); i++)
    {
        PathNode* pathNode = m_PathNodeOpen.at(i);
        if(m_Level->getTileIndexForTile(pathNode->getTile()) == tileIndex)
        {
            return pathNode;
        }
    }
    
    //The tile doesn't exist in the open list, return NULL
    return NULL;
}

bool PathFinder::isSearchingPath()
{
    return m_State == StateSearchingPath;
}

int PathFinder::getPathSize()
{
    return m_PathNodeFinal.size();
}

void PathFinder::sortOpenList()
{
    std::sort(m_PathNodeOpen.begin(), m_PathNodeOpen.end(), PathNode::compareNodes);
}

PathNode* PathFinder::getPathNodeAtIndex(int aIndex)
{
    if(aIndex >= 0 && aIndex < getPathSize())
    {
        return m_PathNodeFinal.at(aIndex);
    }
    return NULL;
}

void PathFinder::addPathNodeToOpenList(PathNode* aPathNode)
{
	//Insert the Path node into the Open path node vector
	m_PathNodeOpen.push_back(aPathNode);
    
    //Sort the open list
    sortOpenList();
}

void PathFinder::buildFinalNodePath(PathNode* aPathNode)
{
	do
	{
        //Safety check the parentNode
		if(aPathNode->getParentNode() != NULL)
		{
			m_PathNodeFinal.insert(m_PathNodeFinal.begin(), aPathNode);
		}
        
		//Set the tile path flag to true
		aPathNode->getTile()->setIsPath(true);
        
		//Set the path node's pointer to it's parent
		aPathNode = aPathNode->getParentNode();
	}
	while (aPathNode != NULL);
}

void PathFinder::clearPathNodes()
{
	//Now cycle through the Open node path vector, and delete all the path node
	while(m_PathNodeOpen.size() > 0)
	{
		//Get the last element in the vector
		PathNode* node = m_PathNodeOpen.back();
        
		//Delete the path node
		delete node;
        
		//Remove the last element in the vector
		m_PathNodeOpen.pop_back();
	}
    
	//Lastly cycle through the Closed node path vector, and delete all the path node
	while(m_PathNodeClosed.size() > 0)
	{
		//Get the last element in the vector
		PathNode* node = m_PathNodeClosed.back();
        
		//Delete the path node
		delete node;
        
		//Remove the last element in the vector
		m_PathNodeClosed.pop_back();
	}
    
    //Clear the final path node list
    m_PathNodeFinal.clear();
    
    //Reset the destination tile index
    m_DestinationTileIndex = -1;
}

void PathFinder::togglePathFindingDelay()
{
    m_EnableSearchDelay = !m_EnableSearchDelay;
}

int PathFinder::getManhattanDistanceCost(Tile* aStartTile, Tile* aDestinationTile)
{
	//Here we use the Manhattan method, which calculates the total number of step moved horizontally and vertically to reach the
	//final desired step from the current step, ignoring any obstacles that may be in the way
	int distance = abs(m_Level->getTileCoordinateForPosition(aDestinationTile->getX()) - m_Level->getTileCoordinateForPosition(aStartTile->getX())) 
    + abs(m_Level->getTileCoordinateForPosition(aDestinationTile->getY()) - m_Level->getTileCoordinateForPosition(aStartTile->getY()));
    
    //Return the distance between the two tiles
	return distance;
}