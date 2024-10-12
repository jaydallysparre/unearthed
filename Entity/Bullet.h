#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

/*
* Basic projectile object modelled as a point.
*/

class Bullet {
private:
    sf::Vector2f direction;
    int speed;
    int damage;
    Team team;
    sf::Texture spriteTexture;
    sf::Sprite sprite;
public:
    Bullet(sf::Vector2f direction, sf::Vector2f spawnPos, Team team, int damage, int speed);
    int getDamage();
    Team getTeam();
    void move(float dt);
    void draw(sf::RenderWindow& window);
    bool isWorldColliding(Level& level);
    bool isEntityColliding(Entity* entity);
};

#endif