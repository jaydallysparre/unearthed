#ifndef AIINPUT_H
#define AIINPUT_H

#include "InputHandler.h"
#include "Entity.h"
#include "MathUtil.h"
#include <stack>

class AIInput : public InputHandler {
    Entity* target; // Player to target
    Level* level; // For pathfinding
    std::vector<std::vector<AINode>> nodeMap;
    std::stack<AINode*> path;
    sf::Clock timer;
public:
    AIInput(Entity* player, Level* level);
    int heuristic(AINode& begin, AINode& end); 
    std::stack<AINode*> findPath(AINode& begin, AINode& end);
    std::vector<std::vector<AINode>> generateNodeMap();
    void resetNodeMap();
    std::vector<AINode*> getNeighbours(AINode* node);
    sf::Vector2f getNodeDirection(sf::Vector2f entityOrigin, AINode& node);
    std::stack<AINode*> getNodePath();
    void handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window);
};

#endif