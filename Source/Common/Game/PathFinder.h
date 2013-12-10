//
//  PathFinder.h
//  GAM-1532 OSX Game
//
//  Created by Bradley Flood on 2013-03-07.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <vector>

#define PATH_FINDING_DELAY 1.0

class Level;
class Tile;
class PathNode;
class PathFinderListener;

class PathFinder
{
public:
    PathFinder(Level* level, PathFinderListener* listener);
    ~PathFinder();
    
    void findPath(Tile* currentTile, Tile* destinationTile);
    
    void update(double delta);
    void paint(); //Only paint in debug mode, draws the G, H and F scores
    void reset();
    
    bool isSearchingPath();
    
    int getPathSize();
    PathNode* getPathNodeAtIndex(int index);
    
    void togglePathFindingDelay();
    
private:
    void addAdjacentTile(std::vector<Tile*>& adjacentTiles, Tile* currentTile, int deltaX, int deltaY);
    
    bool doesTileExistInClosedList(Tile* tile);
    bool doesTileExistInOpenList(Tile* tile);
    
    PathNode* getOpenPathNodeForTile(Tile* tile);
    
    void sortOpenList();
    void addPathNodeToOpenList(PathNode* pathNode);
    
	void buildFinalNodePath(PathNode* pathNode);
    void clearPathNodes();
    
	int getManhattanDistanceCost(Tile* startTile, Tile* destinationTile);
    
    //Enum to keep track of the internal state of the path finder
    enum PathFinderState
    {
        StateIdle = 0,
        StateSearchingPath,
        StateFoundPath,
        StateError
    };
    
    //Member variables
    Level* m_Level;
    PathFinderListener* m_Listener;
    PathFinderState m_State;
    int m_DestinationTileIndex;
    double m_SearchDelay;
    bool m_EnableSearchDelay;
	std::vector<PathNode*> m_PathNodeOpen;
	std::vector<PathNode*> m_PathNodeClosed;
	std::vector<PathNode*> m_PathNodeFinal;
};

class PathFinderListener
{
public:
    virtual void pathFinderFinishedSearching(PathFinder* pathFinder, bool pathWasFound) = 0;
};


#endif
