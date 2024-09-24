#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <limits>


struct AINode {
    AINode(int x, int y, bool traversable) : x(x), y(y), traversable(traversable) {}
    void resetAIParams() {
        gCost = fCost = std::numeric_limits<int>::infinity();
        hCost = 0;
        parent = nullptr;
    }
    int x;
    int y;
    bool traversable;
    int gCost = std::numeric_limits<int>::infinity();
    int hCost = 0;
    int fCost = std::numeric_limits<int>::infinity();
    AINode* parent = nullptr;
};


/*
* Level objects contain multiple representations of the level, for drawing, collisions and AI.
*/
class Level {
private:
    std::vector<std::vector<int>> level;
    std::vector<std::vector<int>> collisionMap; // entities's positions are projected onto this for collisions
    std::vector<int> collidableTiles; // allow map maker to define which tiles are collidable on level creation
    std::vector<std::vector<AINode>> nodeMap; // AI uses this for A* pathfinding
    sf::Texture spritesheet;
    int tileSize;
public:
    Level();
    Level(std::string lvlFilename, std::string spriteFilename, int tileSize, std::vector<int> collidableTiles);
    bool loadSpriteSheet(std::string filename, int tileSize);
    bool loadFromFile(std::string filename);
    int getTileSize();
    std::vector<std::vector<int>> generateCollisionMap();
    std::vector<std::vector<int>> getCollisionMap();

    // Pathfinding helper methods
    std::vector<std::vector<AINode>> generateNodeMap();
    std::vector<std::vector<AINode>> getNodeMap();
    std::vector<AINode*> getNeighbours(AINode* node);

    void display(sf::RenderWindow& window);
};

#endif