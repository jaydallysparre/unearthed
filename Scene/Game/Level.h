#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <limits>
#include "EnemyType.h"
#include <utility>
#include <random>

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
    std::mt19937 mt{std::random_device{}()}; // For randomness
    std::vector<std::pair<int,int>> openSquares;
    std::vector<int> collidableTiles; // allow map maker to define which tiles are collidable on level creation
    sf::Texture spritesheet;
    int tileSize;
    std::vector<EnemyType::Enemy> allowedEnemies;
public:
    Level();
    Level(std::string lvlFilename, std::string spriteFilename, int tileSize, std::vector<int> collidableTiles, std::vector<EnemyType::Enemy> allowedEnemies);
    bool loadSpriteSheet(std::string filename, int tileSize);
    bool loadFromFile(std::string filename);
    int getTileSize();
    std::vector<std::vector<int>> generateCollisionMap();
    std::vector<std::vector<int>> getCollisionMap();
    std::vector<EnemyType::Enemy> getAllowedEnemys();
    std::pair<int, int> getOpenSquare(); // get a tile that is not a wall.
    void display(sf::RenderWindow& window);
};

#endif