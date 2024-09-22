#include "BulletManager.h"

void BulletManager::addBullet(Bullet* bullet) {
    bullets.push_back(bullet);
}

void BulletManager::removeBullet(int idx) {
    delete bullets[idx];
    bullets.erase(bullets.begin() + idx);
}

void BulletManager::update(Level& level, std::vector<Entity*> entities, float dt) {
    for (int i = 0; i < bullets.size(); ++i) {
        bullets[i]->move(dt);
        if (bullets[i]->isWorldColliding(level)) {
            removeBullet(i);
        }
        for (int j = 0; j < entities.size(); j++) {
            if (bullets[i]->isEntityColliding(entities[j]) && entities[j]->getTeam() != bullets[i]->getTeam()) {
                entities[j]->takeDamage(bullets[i]->getDamage());
                removeBullet(i);
            }
        }
    }
}

void BulletManager::display(sf::RenderWindow& window) {
    for (Bullet* bullet: bullets) {
        bullet->draw(window);
    }
}