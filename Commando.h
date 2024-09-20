#ifndef COMMANDO_H
#define COMMANDO_H

#include "Entity.h"

class Commando : public Entity {
public:
    Commando(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team);
    void attack(sf::Vector2i attackDir) {}
};

#endif