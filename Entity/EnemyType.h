#ifndef ENEMY_TYPE
#define ENEMY_TYPE

#include <SFML/Graphics.hpp>
#include <vector>

/*
* Stores enemy types, their costs
*/

class EnemyType {
    private:
    int enemyAmount = 1;
public:
    enum Enemy {
        Ghost
    };
    static int getEnemyAmount();
    static int getCost(Enemy enemy);
};

#endif