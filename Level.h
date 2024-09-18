#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Level {
private:
    std::vector<std::vector<int>> level;
    std::vector<std::vector<int>> collisionMap;
    std::vector<int> collidableTiles;
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
    void display(sf::RenderWindow& window);
};

#endif