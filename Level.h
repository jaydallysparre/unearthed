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
    sf::Texture spritesheet;
    int tileSize;
public:
    Level();
    Level(std::string lvlFilename, std::string spriteFilename, int tileSize);
    bool loadSpriteSheet(std::string filename, int tileSize);
    bool loadFromFile(std::string filename);
    void display(sf::RenderWindow& window);
};

#endif