#ifndef DIRECTOR_H
#define DIRECTOR_H

class GameScene; // Forward declaration to avoid problems, as they rely on eachother.

#include "Level.h"
#include "EnemyType.h"
#include "Entity.h"
#include "GameScene.h"
#include "Ghost.h"
#include "AIInput.h"
#include "Interactable.h"
#include "Chest.h"
#include <queue>

/*
* Director class that handles spawning entities and chests in the stage.
*/

class Director {
private:
    GameScene* gamescene;
    sf::Clock directorTimer;
    sf::Clock chestSpawnTimer;
    int enemyCredits = 0;
    int stageCredits;
    std::queue<EnemyType::Enemy> spawnQueue;
    sf::Clock enemySpawnTimer;

    // Spawns enemies with gamescene
    void spawnEnemy(EnemyType::Enemy enemy);

    // Spend its accumulated credit to add enemies to the spawn queue
    void spendCredits();

    // Accumulate credits
    void updateCredits();
public:
    Director(GameScene* gamescene);
    
    // Populate the stage with chests
    void populateStage();

    // Call its internal functions
    void update();
};

#endif