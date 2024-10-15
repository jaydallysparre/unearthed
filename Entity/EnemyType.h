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

    // Returns the amount of enemy types that have been implemented
    static int getEnemyAmount();
    
    // returns the cost of the enemy
    static int getCost(Enemy enemy);
};

#endif