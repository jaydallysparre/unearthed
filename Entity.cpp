#include "Entity.h"

Entity::Entity(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team) : inputHandler(inputHandler), team(team) {
    sprite.move(spawnPos);
}

void Entity::move(sf::Vector2f direction, float dt) {
    std::cout << direction.x << ","  << direction.y << "|" << speed << '\n';
    sprite.move(direction.x * speed * dt, direction.y * speed *dt);
}

void Entity::listenToInput(float dt) {
    inputHandler->handleInputs();
    if (inputHandler->isMoving() && canMove) {
        move(inputHandler->getMoveDir(), dt);
    }
    if (inputHandler->isAttacking() && canAttack) {
        attack(inputHandler->getAttackDir());
    }
}

void Entity::display(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Entity::update(sf::RenderWindow& window, float dt) {
    listenToInput(dt);
    display(window);
}