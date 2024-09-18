#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "HBSprite.h"
#include <iostream>

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
    sf::Vector2f velocity;
    InputHandler* inputHandler;
    Team team;
    sf::Texture spriteTexture;
    HBSprite sprite;
    Entity(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team);
public:
    void virtual move(sf::Vector2f direction, float dt);
    void virtual attack(sf::Vector2i attackDir) = 0;
    void virtual takeDamage(int dmgAmount) = 0;
    void listenToInput(float dt);
    void display(sf::RenderWindow& window);
    void virtual update(sf::RenderWindow& window, float dt);
};

#endif