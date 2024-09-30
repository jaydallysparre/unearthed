#include "Director.h"
#include <random>

Director::Director(GameScene* gamescene) :gamescene(gamescene){
    std::cout << "INIT CREDITS = " << enemyCredits << '\n';
}

void Director::populateStage() {

}

void Director::spawnEnemy(EnemyType::Enemy enemy) {
    Entity* enemyEntity; 
    Level* level = gamescene->getLevel();
    std::pair<int, int> coordinates = gamescene->getLevel()->getOpenSquare();
    int tilesize = level->getTileSize();
    coordinates.first *= tilesize;
    coordinates.second *= tilesize;
    switch (enemy) {
        case EnemyType::Enemy::Ghost:
            enemyEntity = new Ghost(new AIInput(gamescene->getPlayer(), gamescene->getLevel()), sf::Vector2f(coordinates.second, coordinates.first), Team::ENEMY, gamescene->getBulletManager());
            break;
    }
    std::cout << "Enemy spawned at " << coordinates.first << ", " << coordinates.second << '\n';
    gamescene->addEnemy(enemyEntity);
}

void Director::spendCredits() {
    std::cout << "Spend Credits: " << enemyCredits << '\n';
    std::vector<EnemyType::Enemy> allowedEnemies = gamescene->getLevel()->getAllowedEnemys();
    std::random_shuffle(allowedEnemies.begin(), allowedEnemies.end());
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution boolean{0,1}; // random boolean

    int minEnemyCredit = allowedEnemies[0];
    for (EnemyType::Enemy enemy: allowedEnemies) {
        if (minEnemyCredit < EnemyType::getCost(enemy)) {
            minEnemyCredit = EnemyType::getCost(enemy);
        }
    }
    std::cout << "min cost = " << minEnemyCredit << '\n';
    while (enemyCredits >= minEnemyCredit) {
    for (EnemyType::Enemy enemy : allowedEnemies) {
        int enemyCost = EnemyType::getCost(enemy);
        while (boolean(mt) && enemyCost <= enemyCredits) {
            spawnEnemy(enemy);
            enemyCredits -= enemyCost;
        }
    }
    }
    std::cout << "Credits Left:" << enemyCredits << '\n';
}

void Director::updateCredits() {
    enemyCredits += 2;
    std::cout << "credits after update = " << enemyCredits << '\n';
}

void Director::update() {
    if (directorTimer.getElapsedTime().asSeconds() > 8) {
        directorTimer.restart();
        updateCredits();
        std::mt19937 mt{std::random_device{}()};
        // there is a 60% chance of spawning enemies
        std::uniform_real_distribution<float> spawnThreshold{0,1};
        if (spawnThreshold(mt) > 0.4) {
            spendCredits();
        }
    }
}