#include "EnemyType.h"

int EnemyType::getCost(Enemy enemy) {
    switch (enemy) {
        case Ghost:
            return 2;
            break;
        default:
            return 0;
            break;
    }
}