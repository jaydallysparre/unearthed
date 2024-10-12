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
public:
    Director(GameScene* gamescene);
    void populateStage();
    void spawnEnemy(EnemyType::Enemy enemy);
    void spendCredits();
    void updateCredits();
    void update();
};

#endif