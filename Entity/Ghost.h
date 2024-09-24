#ifndef GHOST_H
#define GHOST_H

#include "RangedEntity.h"

class Ghost : public RangedEntity {
public:
    Ghost(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team, BulletManager* bulletManger);
};

#endif