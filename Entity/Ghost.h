#ifndef GHOST_H
#define GHOST_H

#include "RangedEntity.h"

/*
* Basic ranged enemy class.
*/

class Ghost : public RangedEntity {
public:
    Ghost(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team, BulletManager* bulletManger, float timeFactor, sf::Texture& texture);
};

#endif