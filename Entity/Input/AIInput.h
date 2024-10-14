#ifndef AIINPUT_H
#define AIINPUT_H

#include "InputHandler.h"
#include "Entity.h"
#include "MathUtil.h"
#include <stack>
#include "AINode.h"
/*
* AI Input handler class. Contains functions to handle pathfinding to a player.
*/

class AIInput : public InputHandler {
private:
    Entity* target; // Player to target
    Level* level; // For pathfinding
    std::vector<std::vector<AINode>> nodeMap;
    std::stack<AINode*> path;
    sf::Clock timer;
    int heuristic(AINode& begin, AINode& end); // Gets distance heuristic for A* algorithm. Helper function for findPath
    std::vector<AINode*> getNeighbours(AINode* node); // Gets a nodes neighbour. helper function for findPath
    void resetNodeMap();
    sf::Vector2f getNodeDirection(sf::Vector2f entityOrigin, AINode& node);
public:
    std::vector<std::vector<AINode>> generateNodeMap();
    std::stack<AINode*> findPath(AINode& begin, AINode& end); // Finds a path to the player
    AIInput(Entity* player, Level* level);
    std::stack<AINode*> getNodePath();
    void handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window);
};

#endif