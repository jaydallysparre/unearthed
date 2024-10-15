#include "BulletManager.h"

BulletManager::~BulletManager() {
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
}

void BulletManager::addBullet(Bullet* bullet) {
    bullets.push_back(bullet);
}

void BulletManager::removeBullet(int idx) {
    delete bullets[idx];
    bullets.erase(bullets.begin() + idx);
}

void BulletManager::update(Level& level, Entity** entities, int entityCount, Entity* player, float dt) {
    for (int i = 0; i < bullets.size(); ++i) {
        bullets[i]->move(dt);
        if (bullets[i]->isWorldColliding(level)) {
            removeBullet(i);
        }
        // Check if bullet is colliding with any entity, and make enemy take damage if so
        for (int j = 0; j < entityCount; j++) {
            if (bullets[i]->isEntityColliding(entities[j]) && entities[j]->getTeam() != bullets[i]->getTeam()) {
               entities[j]->takeDamage(bullets[i]->getDamage());
               removeBullet(i);
               break;
            }
        }
        if (bullets[i]->isEntityColliding(player) && player->getTeam() != bullets[i]->getTeam()) {
            player->takeDamage(bullets[i]->getDamage());
            removeBullet(i);
            break;
        }
    }
}

void BulletManager::display(sf::RenderWindow& window) {
    for (Bullet* bullet: bullets) {
        bullet->draw(window);
    }
}