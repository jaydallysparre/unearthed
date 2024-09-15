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
    std::vector<sf::Texture> textures;
    int tileSize;
public:
    Level();
    Level(std::string filename, std::vector<sf::Texture> textures, int tileSize);
    void setTextures(std::vector<sf::Texture> texture, int tileSize);
    bool loadFromFile(std::string filename);
    void display(sf::RenderWindow& window);
};

#endif