#include "Ghost.h"

Ghost::Ghost(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team, BulletManager* bulletManager, float timeFactor) : RangedEntity(inputHandler, spawnPos, team, bulletManager) {
    spriteTexture.loadFromFile("ghost.png");
    sprite.setTexture(spriteTexture);
    sprite.setHitbox({10.f, 5.f, 12.f, 27.f});
    speed = 50 * timeFactor;
    bulletSpeed = 150;
    attackDelay = 0.6;
    maxHealth = health = 100 * timeFactor;
    regen = 1 * timeFactor;
    damage = 30 * timeFactor;
}
