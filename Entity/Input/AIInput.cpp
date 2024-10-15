#include "AIInput.h"
#include <algorithm>
#include <cmath>

AIInput::AIInput(Entity* player, Level* level) : target(player), level(level) {
    generateNodeMap();
}

// The heuristic is used in A* for guessing good next tiles to search
int AIInput::heuristic(AINode& begin, AINode& end) {
    int dx = std::abs(end.x - begin.x);
    int dy = std::abs(end.y - begin.y);
    return std::min(dx, dy) * 14 + std::abs(dx - dy) * 10;
}

// Node map is composed of nodes which will have costs, and whether they are traversable or not
std::vector<std::vector<AINode>> AIInput::generateNodeMap() {
    for (int i = 0; i < level->getCollisionMap().size(); ++i) {
        nodeMap.push_back(std::vector<AINode>{});
        for (int j = 0; j < level->getCollisionMap()[i].size(); ++j) {
            nodeMap[i].push_back(AINode(j, i, !level->getCollisionMap()[i][j]));
        }
    }
    return nodeMap;
}

void AIInput::resetNodeMap() {
    for (std::vector<AINode> vec : nodeMap) {
        for (AINode node : vec) {
            node.resetAIParams();
        }
    }
}

std::vector<AINode*> AIInput::getNeighbours(AINode* node) {
    std::vector<AINode*> neighbours;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (i == 0 && j == 0 || (std::abs(i) == 1 && std::abs(j) == 1)) { // Don't include itself, nor diagonal tiles
                continue;
            }

            // Calculate real X and Y based on node pos
            int newY = node->y + i;
            int newX = node->x + j;
            if ((newY > 0 && newY < nodeMap.size()) && newX > 0 && newX < nodeMap[newY].size()) {
                neighbours.push_back(&nodeMap[newY][newX]);
            }
        }
    }
    return neighbours;
}

std::stack<AINode*> AIInput::findPath(AINode& begin, AINode& end) {
    resetNodeMap();
    std::vector<AINode*> open; // Unsearched nodes
    std::vector<AINode*> closed; // Already searched nodes
    open.push_back(&begin);
    begin.gCost = 0;
    begin.fCost = heuristic(begin, end);
    while (!open.empty()) {
        int currentIdx = 0;
        for (int i = 1; i < open.size(); ++i) {
            if (open[i]->fCost < open[currentIdx]->fCost) {
                currentIdx = i;
            }
        }
        
        AINode* current = open[currentIdx];
        
        if (current->x == end.x && current->y == end.y) { // goal reached
            std::stack<AINode*> path;
            while (current != nullptr) {
                path.push(current);
                current = current->parent;
            }
            return path;
        }

        open.erase(open.begin() + currentIdx);
        closed.push_back(current);
        
        std::vector<AINode*> neighbours = getNeighbours(current);
        for (AINode* neighbour : neighbours) {
            if (!neighbour->traversable || (std::find(closed.begin(), closed.end(), neighbour) != closed.end())) {
                continue; // skip if neighbour in closed set or is a wall
            }
            int potentialGCost = current->gCost + ((std::abs(neighbour->x - current->x) + std::abs(neighbour->y - current->y)) == 2? 14: 10);

            if (!(std::find(open.begin(), open.end(), neighbour) != open.end())) {
                open.push_back(neighbour);
            } else if (potentialGCost >= neighbour->gCost) {
                continue;
            }

            neighbour->parent = current;
            neighbour->gCost = potentialGCost;
            neighbour->hCost = heuristic(*neighbour, end);
            neighbour->fCost =  neighbour->gCost + neighbour->hCost;
        }
    }
   return std::stack<AINode*>{};
}

sf::Vector2f AIInput::getNodeDirection(sf::Vector2f entityOrigin, AINode& node) {
    return MathUtil<sf::Vector2f>::normalize(sf::Vector2f(node.x*32+16, node.y*32+16) - entityOrigin);
}

std::stack<AINode*> AIInput::getNodePath() {
    return path;
}

void AIInput::handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window) {
    move = false;
    
    // Recalculate target based on distance between enemy and player.
    // Enemies at a distance require less precise pathfinding than those closer
    float calcTime = 0.5 + std::log10(MathUtil<sf::Vector2f>::distance(entityOrigin, target->getOrigin())/100 + 1);
    if (timer.getElapsedTime().asSeconds() > calcTime) {
        AINode selfNode = AINode(entityOrigin.x/level->getTileSize(), entityOrigin.y/level->getTileSize(), true);
        AINode targetNode = AINode(target->getOrigin().x/level->getTileSize(), target->getOrigin().y/level->getTileSize(), true);

        path = findPath(selfNode, targetNode);
        timer.restart();
    }
    
    if (!path.empty()) { // Let's go to the next node in our node path
        moveDir = getNodeDirection(entityOrigin, *path.top());
        sf::Vector2f nextNode(path.top()->x*32+16, path.top()->y*32+16);
        if (MathUtil<sf::Vector2f>::distance(entityOrigin, nextNode) <= 16) {
            path.pop();
        }
        move = true;
    }
    
    // Attack enemy if close enough
    attack = false;
    sf::Vector2f targetOrigin = target->getOrigin();
    if (MathUtil<sf::Vector2f>::distance(entityOrigin, targetOrigin) <= 300) {
        attack = true;
        attackDir = MathUtil<sf::Vector2f>::normalize(targetOrigin - entityOrigin);
    }

}
