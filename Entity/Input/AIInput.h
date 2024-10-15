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
    friend class Tester;
private:
    Entity* target; // Player to target
    Level* level; // For pathfinding
    std::vector<std::vector<AINode>> nodeMap;
    std::stack<AINode*> path;
    sf::Clock timer;

    // Gets distance heuristic for A* algorithm. Helper function for findPath
    int heuristic(AINode& begin, AINode& end);

    // Gets a nodes neighbours. helper function for findPath
    std::vector<AINode*> getNeighbours(AINode* node);

    // Resets node map cost values for next pathfind
    void resetNodeMap(); 

    // Get direction from entity origin to node
    sf::Vector2f getNodeDirection(sf::Vector2f entityOrigin, AINode& node); 

    // generate map of nodes from the level collision data
    std::vector<std::vector<AINode>> generateNodeMap(); 

    // Finds a path to the player using the A* algorithm
    std::stack<AINode*> findPath(AINode& begin, AINode& end); 
public:
    AIInput(Entity* player, Level* level);

    // Returns node path returned by findpath
    std::stack<AINode*> getNodePath();

    // Sets attributes to be read by owner entity
    void handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window);
};

#endif