#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "HBSprite.h"
#include <iostream>
#include <vector>
#include <array>
#include "Level.h"
#include "Healthbar.h"

enum class Team { // TO FIX
    ALLY,
    ENEMY
};

/*
* Base abstract entity class. Contains attributes and methods that apply/could apply to all enemies.
*/

class Entity {
protected:
    int health;
    int maxHealth;
    int regen;
    int damage;
    int speed;
    bool canMove = true;
    bool canAttack = true;
    float attackDelay = 0.3;
    sf::Clock attackTimer;
    sf::Clock regenTimer;
    sf::Vector2f velocity;;
    InputHandler* inputHandler;
    Team team;
    sf::Texture spriteTexture;
    HBSprite sprite;
    Healthbar* healthbar;
    bool showHealthbar;
    Entity(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team);
public:
    virtual ~Entity();
    void virtual move(sf::Vector2f direction, Level& level, float dt);
    void virtual attack(sf::Vector2f attackDir) = 0;
    void virtual takeDamage(int dmgAmount);

    int getHealth();
    int getMaxHealth();
    Team getTeam();
    InputHandler* getInputHandler();
    sf::Vector2f getPosition();
    sf::Vector2f getOrigin(); // Get center of hitbox
    bool isDead();

    void upgradeMaxHealth(int amount);
    void upgradeAttackSpeed(float amount);
    void upgradeAttackDamage(int amount);
    void upgradeRegen(int amount);
    void upgradeSpeed(int amount);
    void healToFull();

    void flipSprite(bool flip);
    void listenToInput(float dt, Level& level, sf::RenderWindow& window);
    void display(sf::RenderWindow& window);
    bool isColliding(Level& level);
    bool pointInEntity(sf::Vector2f point);
    
    void virtual update(sf::RenderWindow& window, Level& level, float dt);
};

#endif