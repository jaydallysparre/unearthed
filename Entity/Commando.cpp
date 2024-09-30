#include "Commando.h"

Commando::Commando(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team, BulletManager* bulletManager) : RangedEntity(inputHandler, spawnPos, team, bulletManager) {
    spriteTexture.loadFromFile("commando_idle.png");
    sprite.setTexture(spriteTexture);
    sprite.setHitbox({8.f, 0.f, 16.f, 32.f});
    speed = 140;
    bulletSpeed = 500;
    health = 300;
    maxHealth = 300;
    regen = 3;
    damage = 10;
}
