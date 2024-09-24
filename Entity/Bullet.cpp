#include "Bullet.h"

Bullet::Bullet(sf::Vector2f direction, sf::Vector2f spawnPos, Team team, int damage, int speed) : direction(direction), team(team), damage(damage), speed(speed) {
    sprite.setPosition(spawnPos);
    spriteTexture.loadFromFile("bullet.png");
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

bool Bullet::isWorldColliding(Level& level) {
    std::vector<std::vector<int>> collisionMap = level.getCollisionMap();
    sf::Vector2f bulletPos = sprite.getPosition();
    int tileSize = level.getTileSize();
    return collisionMap[bulletPos.y/tileSize][bulletPos.x/tileSize] == 1; 
}

bool Bullet::isEntityColliding(Entity* entity) {
    return entity->pointInEntity(sprite.getPosition());
}