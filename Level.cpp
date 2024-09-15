#include "Level.h"

Level::Level() {}

Level::Level(std::string filename, std::vector<sf::Texture> textures, int tileSize): textures(textures), tileSize(tileSize) {
    loadFromFile(filename);
}

bool Level::loadFromFile(std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error! " << filename << " could not be opened!" << '\n';
        return false;
    }
    std::string str;
    int v;
    while (std::getline(file, str)) { 
        std::vector<int> temp;
        std::istringstream ss(str);
        while (ss >> v) {
            temp.push_back(v);
        }
        level.push_back(temp);
    } 
    return true;
}

void Level::setTextures(std::vector<sf::Texture> textures, int tileSize) {
    this->tileSize = tileSize;
    this->textures = textures;
}

void Level::display(sf::RenderWindow& window) {
    for (int i = 0; i < level.size(); ++i) {
        for (int j = 0; j < level[i].size(); ++j) {
            sf::VertexArray tile(sf::TriangleStrip, 4);
            int xOff = j*32;
            int yOff = i*32;
            tile[0].position = sf::Vector2f(xOff, yOff);
            tile[1].position = sf::Vector2f(xOff, 32+yOff);
            tile[2].position = sf::Vector2f(32+xOff, yOff);
            tile[3].position = sf::Vector2f(32+xOff, 32+yOff);
            tile[0].texCoords = sf::Vector2f(0, 0);
            tile[1].texCoords = sf::Vector2f(0, 32);
            tile[2].texCoords = sf::Vector2f(32, 0);
            tile[3].texCoords = sf::Vector2f(32, 32);
            window.draw(tile, &textures[level[i][j]]);
        }
    }
}
