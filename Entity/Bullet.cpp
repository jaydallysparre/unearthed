#include "Bullet.h"

Bullet::Bullet(sf::Vector2f direction, sf::Vector2f spawnPos, Team team, int damage, int speed) : direction(direction), team(team), damage(damage), speed(speed) {
    sprite.setPosition(spawnPos);
    spriteTexture.loadFromFile("img/bullet.png");
    sprite.setTexture(spriteTexture);
}

int Bullet::getDamage() {
    return damage;
}

Team Bullet::getTeam() {
    return team;
}

void Bullet::move(float dt) {
   sprite.move(direction.x * speed * dt, direction.y * speed * dt) ;
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Projects bullet onto the collision map and detects if it is colliding.

bool Bullet::isWorldColliding(Level& level) {
    std::vector<std::vector<int>> collisionMap = level.getCollisionMap();
    sf::Vector2f bulletPos = sprite.getPosition();
    int tileSize = level.getTileSize();
    if (bulletPos.y < 0 || bulletPos.x < 0) {
        return false;
    }
    return collisionMap[bulletPos.y/tileSize][bulletPos.x/tileSize] == 1; 
}

bool Bullet::isEntityColliding(Entity* entity) {
    return entity->pointInEntity(sprite.getPosition());
}