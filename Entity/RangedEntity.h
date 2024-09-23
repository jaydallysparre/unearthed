#ifndef RANGEDENTITY_H
#define RANGEDENTITY_H

#include "Entity.h"
#include "BulletManager.h"


class RangedEntity : public Entity {
protected:
    RangedEntity(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team, BulletManager* bulletManager) : Entity(inputHandler, spawnPos, team), bulletManager(bulletManager) {}
    BulletManager* bulletManager; // When bullets are created they are registered with the bullet manager
public:
    virtual ~RangedEntity() = default;
    void attack(sf::Vector2f attackDir) {
        Bullet* bullet = new Bullet(attackDir, getOrigin(), team, damage);
        bulletManager->addBullet(bullet);
    }
};

#endif