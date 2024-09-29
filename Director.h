#ifndef DIRECTOR_H
#define DIRECTOR_H

class GameScene;

#include "Level.h"
#include "EnemyType.h"
#include "Entity.h"
#include "GameScene.h"
#include "Entity/Ghost.h"
#include "AIInput.h"

class Director {
private:
    GameScene* gamescene;
    sf::Clock directorTimer;
    int enemyCredits;
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