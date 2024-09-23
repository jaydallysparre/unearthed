#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet {
private:
    sf::Vector2f direction;
    int speed = 500;
    int damage;
    Team team;
    sf::Texture spriteTexture;
    sf::Sprite sprite;
public:
    Bullet(sf::Vector2f direction, sf::Vector2f spawnPos, Team team, int damage);
    int getDamage();
    Team getTeam();
    void move(float dt);
    void draw(sf::RenderWindow& window);
    bool isWorldColliding(Level& level);
    bool isEntityColliding(Entity* entity);
};

#endif