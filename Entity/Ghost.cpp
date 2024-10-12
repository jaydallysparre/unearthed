#include "Ghost.h"

Ghost::Ghost(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team, BulletManager* bulletManager, float timeFactor, sf::Texture& texture) : RangedEntity(inputHandler, spawnPos, team, bulletManager) {
    spriteTexture = texture;
    sprite.setTexture(spriteTexture);
    sprite.setHitbox({10.f, 5.f, 12.f, 27.f});
    speed = 50 * timeFactor;
    bulletSpeed = 200;
    attackDelay = 0.6;
    maxHealth = health = 100 * timeFactor;
    regen = 1 * timeFactor;
    damage = 30 * timeFactor;
}
