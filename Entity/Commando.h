#ifndef COMMANDO_H
#define COMMANDO_H

#include "RangedEntity.h"

/*
* Basic player class. No special abilites, can move, and shoot.
*/

class Commando : public RangedEntity {
public:
    Commando(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team, BulletManager* bulletManger);
};

#endif