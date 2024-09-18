#include "Level.h"

Level::Level() {}

Level::Level(std::string lvlFilename, std::string spriteFilename, int tileSize) {
    loadFromFile(lvlFilename);
    loadSpriteSheet(spriteFilename, tileSize);
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

bool Level::loadSpriteSheet(std::string filename, int tileSize) {
    this->tileSize = tileSize;
    return spritesheet.loadFromFile(filename);
}


void Level::display(sf::RenderWindow& window) {
    for (int i = 0; i < level.size(); ++i) {
        for (int j = 0; j < level[i].size(); ++j) {
            int sIdx = level[i][j]; // sprite index
            if (sIdx != -1) {
                sf::VertexArray tile(sf::TriangleStrip, 4);
                int xOff = j*32;
                int yOff = i*32;

                // Tile Position
                tile[0].position = sf::Vector2f(xOff, yOff);
                tile[1].position = sf::Vector2f(xOff, tileSize+yOff);
                tile[2].position = sf::Vector2f(tileSize+xOff, yOff);
                tile[3].position = sf::Vector2f(tileSize+xOff, tileSize+yOff);

                // Tile spritesheet offset
                tile[0].texCoords = sf::Vector2f(tileSize*sIdx, 0);
                tile[1].texCoords = sf::Vector2f(tileSize*sIdx, tileSize);
                tile[2].texCoords = sf::Vector2f(tileSize+tileSize*sIdx, 0);
                tile[3].texCoords = sf::Vector2f(tileSize+tileSize*sIdx, tileSize);
                window.draw(tile, &spritesheet);
            }
        }
    }
}
