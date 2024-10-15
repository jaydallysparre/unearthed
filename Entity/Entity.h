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
friend class Tester;
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
    bool showHealthbar; // will be false for the player
    Entity(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team);

    // Flips the direction of the sprite, where flip sends it left, and !flip sends it right
    void flipSprite(bool flip);
public:
    virtual ~Entity();

    // Move the player in a direction, if collisions allow
    void virtual move(sf::Vector2f direction, Level& level, float dt);

    // Virtual attack, to be implemented by derived class
    void virtual attack(sf::Vector2f attackDir) = 0;
    
    // Take specified damage amount
    void virtual takeDamage(int dmgAmount);

    // Getters
    int getHealth();
    int getMaxHealth();
    Team getTeam();
    InputHandler* getInputHandler();
    sf::Vector2f getPosition();
    sf::Vector2f getOrigin(); 

    // Return if health <= 0
    bool isDead();

    // Upgrade entity attributes
    void upgradeMaxHealth(int amount);
    void upgradeAttackSpeed(float amount);
    void upgradeAttackDamage(int amount);
    void upgradeRegen(int amount);
    void upgradeSpeed(int amount);
    void healToFull();

    // Listen to input handler signals
    void listenToInput(float dt, Level& level, sf::RenderWindow& window);

    // Display player in window
    void display(sf::RenderWindow& window);

    // Check collisions
    bool isColliding(Level& level);
    bool pointInEntity(sf::Vector2f point);
    
    // Update
    void virtual update(sf::RenderWindow& window, Level& level, float dt);
};

#endif