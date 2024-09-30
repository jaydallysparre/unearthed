#include "Ghost.h"

Ghost::Ghost(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team, BulletManager* bulletManager) : RangedEntity(inputHandler, spawnPos, team, bulletManager) {
    spriteTexture.loadFromFile("ghost.png");
    sprite.setTexture(spriteTexture);
    sprite.setHitbox({10.f, 5.f, 12.f, 27.f});
    speed = 50;
    bulletSpeed = 150;
    attackDelay = 0.6;
    health = 100;
    maxHealth = 100;
    regen = 1;
    damage = 30;
}
