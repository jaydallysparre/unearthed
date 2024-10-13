#include "Level.h"
#include <chrono>

Level::Level() {}

Level::Level(std::string lvlFilename, std::string spriteFilename, int tileSize, std::vector<int> collidableTiles, std::vector<EnemyType::Enemy> allowedEnemies) : collidableTiles(collidableTiles), allowedEnemies(allowedEnemies) {
    loadFromFile(lvlFilename);
    loadSpriteSheet(spriteFilename, tileSize);
    generateCollisionMap();
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

int Level::getTileSize() {
    return tileSize;
}

bool Level::loadSpriteSheet(std::string filename, int tileSize) {
    this->tileSize = tileSize;
    return spritesheet.loadFromFile(filename);
}

std::vector<std::vector<int>> Level::generateCollisionMap() {
    for (int i = 0; i < level.size(); ++i) {
        std::vector<int> row;
        collisionMap.push_back(row);
        for (int j = 0; j < level[i].size(); ++j) {
            bool isCollidable = false;
            for (int tile = 0; tile < collidableTiles.size(); ++tile) {
                if (collidableTiles[tile] == level[i][j] || level[i][j] == 9) {
                    collisionMap[i].push_back(1);
                    isCollidable = true;
                    break;
                }
            }
            if (!isCollidable) {
                collisionMap[i].push_back(0);
                openSquares.push_back(std::pair<int,int>{i, j});
            }
        }
    }
    return collisionMap;
}

std::vector<std::vector<int>> Level::getCollisionMap() {
    return collisionMap;
}

std::vector<EnemyType::Enemy> Level::getAllowedEnemys() {
    return allowedEnemies;
}

std::pair<int, int> Level::getOpenSquare() {
    std::uniform_int_distribution square{0, (int)openSquares.size()-1};
    return openSquares[square(mt)];
}

void Level::display(sf::RenderWindow& window) {
    for (int i = 0; i < level.size(); ++i) {
        for (int j = 0; j < level[i].size(); ++j) {
            int sIdx = level[i][j]; // sprite index
            if (sIdx != 9) { // 9 is designated empty space tile
                sf::VertexArray tile(sf::TriangleStrip, 4);
                int xOff = j*tileSize;
                int yOff = i*tileSize;

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
