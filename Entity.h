#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "HBSprite.h"
#include <iostream>
#include <vector>
#include <array>
#include "Level.h"

enum class Team {
    ALLY,
    ENEMY
};

class Entity {
protected:
    int health;
    int speed;
    bool canMove = true;
    bool canAttack = true;
    sf::Clock attackTimer;
    sf::Vector2f velocity;
    InputHandler* inputHandler;
    Team team;
    sf::Texture spriteTexture;
    HBSprite sprite;
    Entity(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team);
public:
    void virtual move(sf::Vector2f direction, Level& level, float dt);
    void virtual attack(sf::Vector2f attackDir) = 0;
    void virtual takeDamage(int dmgAmount);
    void listenToInput(float dt, Level& level, sf::RenderWindow& window);
    void display(sf::RenderWindow& window);
    bool isColliding(Level& level);
    sf::Vector2f getPosition();
    sf::Vector2f getOrigin(); // Get center of hitbox
    void virtual update(sf::RenderWindow& window, Level& level, float dt);
};

#endif