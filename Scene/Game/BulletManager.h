#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "Bullet.h"
#include <vector>

/*
* In charge of the bullets in the scene. Has methods for registering and removing the bullets, and updating all of them
*/

class BulletManager {
private:
    std::vector<Bullet*> bullets;
public:
    ~BulletManager();

    // Add bullet to bullet vector
    void addBullet(Bullet* bullet);

    // Remove bullet from bullet vector
    void removeBullet(int idx);

    // Update the positions of all the bullets, and remove them if they are colliding. Damage respective entities
    void update(Level& level, Entity** entities, int entityCount, Entity* player, float dt);

    // Display all bullets
    void display(sf::RenderWindow& window);
};

#endif