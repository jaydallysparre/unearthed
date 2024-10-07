#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "Bullet.h"
#include <vector>

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