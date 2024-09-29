#ifndef ENEMY_TYPE
#define ENEMY_TYPE

/*
* Stores enemy types and their costs for Director
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