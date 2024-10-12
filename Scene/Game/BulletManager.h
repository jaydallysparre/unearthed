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
    void addBullet(Bullet* bullet);
    void removeBullet(int idx);
    void update(Level& level, std::vector<Entity*> entities, Entity* player, float dt);
    void display(sf::RenderWindow& window);
};

#endif