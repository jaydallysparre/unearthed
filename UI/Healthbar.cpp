#include "Healthbar.h"
#include <iostream>

Healthbar::Healthbar(float scale, sf::Vector2f position) {
    shell = sf::RectangleShape(sf::Vector2f(scale*100, scale*20));
    shell.setFillColor(sf::Color(0, 0, 0));
    shell.setPosition(position);
}

sf::Vector2f Healthbar::getSize() {
    return shell.getSize();
}

void Healthbar::draw(sf::Vector2f position, float healthPercentage, sf::RenderWindow& window) {
    shell.setPosition(position);
    window.draw(shell);
    if (healthPercentage > 0) {
        sf::RectangleShape health(sf::Vector2f((shell.getSize().x-2)*healthPercentage, shell.getSize().y-2));
        health.setPosition(shell.getPosition().x+1, shell.getPosition().y+1);
        health.setFillColor(sf::Color(200,0,0));
        window.draw(health);
    }
}