#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "EnemyType.h"
#include "AINode.h"
#include <utility>
#include <random>


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

    // Loads level from file
    bool loadFromFile(std::string filename);

    // Loads spritesheet to be displayed
    bool loadSpriteSheet(std::string filename, int tileSize);
public:
    Level();
    Level(std::string lvlFilename, std::string spriteFilename, int tileSize, std::vector<int> collidableTiles, std::vector<EnemyType::Enemy> allowedEnemies);

    // Generate map of collision data
    std::vector<std::vector<int>> generateCollisionMap();

    // Getters
    int getTileSize();
    std::vector<std::vector<int>> getCollisionMap();
    std::vector<EnemyType::Enemy> getAllowedEnemys();
    std::pair<int, int> getOpenSquare(); // get a random tile that is not a wall.

    // Display level
    void display(sf::RenderWindow& window);
};

#endif