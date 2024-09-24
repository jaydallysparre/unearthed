#include "Level.h"

Level::Level() {}

Level::Level(std::string lvlFilename, std::string spriteFilename, int tileSize, std::vector<int> collidableTiles) : collidableTiles(collidableTiles) {
    loadFromFile(lvlFilename);
    loadSpriteSheet(spriteFilename, tileSize);
    generateCollisionMap();
    generateNodeMap();
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
                if (collidableTiles[tile] == level[i][j]) {
                    collisionMap[i].push_back(1);
                    isCollidable = true;
                    break;
                }
            }
            if (!isCollidable) {
                collisionMap[i].push_back(0);
            }
        }
    }
    return collisionMap;
}

std::vector<std::vector<int>> Level::getCollisionMap() {
    return collisionMap;
}

std::vector<std::vector<AINode>> Level::generateNodeMap() {
    std::vector<std::vector<AINode>> nodeMap;
    for (int i = 0; i < collisionMap.size(); ++i) {
        nodeMap.push_back(std::vector<AINode>{});
        for (int j = 0; j < collisionMap[i].size(); ++j) {
            nodeMap[i].push_back(AINode(j, i, !collisionMap[i][j]));
        }
    }
    this->nodeMap = nodeMap;
    return nodeMap;
}

std::vector<std::vector<AINode>> Level::getNodeMap()  {
    return nodeMap;
}

std::vector<AINode*> Level::getNeighbours(AINode* node) {
    std::vector<AINode*> neighbours;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }
            int newY = node->y + i;
            int newX = node->x + j;
            if ((newY > 0 && newY < nodeMap.size()) && newX > 0 && newX < nodeMap[newY].size()) {
                neighbours.push_back(&nodeMap[newY][newX]);
            }
        }
    }
    return neighbours;
}

void Level::display(sf::RenderWindow& window) {
    for (int i = 0; i < level.size(); ++i) {
        for (int j = 0; j < level[i].size(); ++j) {
            int sIdx = level[i][j]; // sprite index
            if (sIdx != -1) {
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
