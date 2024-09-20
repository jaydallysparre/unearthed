#ifndef RANGEDENTITY_H
#define RANGEDENTITY_H

#include "Entity.h"

class Bullet {
private:
    sf::Vector2f velocity;
    int speed = 300;
    Team team;
    sf::Texture spriteTexture;
public:
    HBSprite sprite;
    Bullet(sf::Vector2f direction, sf::Vector2f spawnPos, Team team) : velocity(direction), team(team) {
        std::cout << direction.x << ", " << direction.y << '\n';
        sprite.setPosition(spawnPos);
        spriteTexture.loadFromFile("bullet.png");
        sprite.setTexture(spriteTexture);
        sprite.setHitbox({2.f, 0.f, 6.f, 0.f});
    }
    void move(float dt) {
     //  std::cout << velocity.x << ", " << velocity.y << '\n';
       sprite.move(velocity.x * speed * dt,velocity.y * speed * dt);
    }
};

class RangedEntity : public Entity {
protected:
    RangedEntity(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team) : Entity(inputHandler, spawnPos, team) {}
    std::vector<Bullet*> bullets;
public:
    void attack(sf::Vector2f attackDir) {
        Bullet* bullet = new Bullet(attackDir, getOrigin(), team);
        std::cout << "attack" << '\n';
        bullets.push_back(bullet);
    }
    void update(sf::RenderWindow &window, Level& level, float dt) {
        Entity::update(window, level, dt);
        for (Bullet* bullet : bullets) {
            bullet->move(dt);
            window.draw(bullet->sprite);
        }
    }
};

#endif