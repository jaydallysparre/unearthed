#include "KBMInput.h"

void KBMInput::handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window) {
    move = true;
    attack = false;
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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        attack = true;
        attackDir = MathUtil<sf::Vector2f>::normalize(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView()) - entityOrigin);
    }
}