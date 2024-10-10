#include "KBInput.h"
#include <iostream>

void KBInput::handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window) {
    moveDir.x = moveDir.y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        moveDir.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        moveDir.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        moveDir.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moveDir.x += 1;
    }
    move = !(moveDir == sf::Vector2f(0,0));

    moveDir = MathUtil<sf::Vector2f>::normalize(moveDir);

    attackDir.x = attackDir.y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        attackDir.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        attackDir.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        attackDir.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        attackDir.x += 1;
    }
    attack = !(attackDir == sf::Vector2f(0, 0));
    attackDir = MathUtil<sf::Vector2f>::normalize(attackDir);
}