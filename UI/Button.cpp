#include "Button.h"
#include <iostream>

Button::Button(std::string txt, sf::Vector2f position, sf::Vector2f size, sf::Font* font, std::function<void()> action) : action(action) {
    text.setFont(*font);
    text.setString(txt);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    // Set origin of text to center for centering on button
    sf::FloatRect bound = text.getLocalBounds();
    text.setOrigin(bound.left+bound.width/2, bound.top+bound.height/2);
    text.setPosition(position.x+size.x/2, position.y+size.y/2);
    body.setSize(size);
    body.setPosition(position);
    body.setFillColor(sf::Color(22, 20, 26, 255));
    body.setOutlineColor(sf::Color(206, 206, 206, 255));
    body.setOutlineThickness(2);
    hitbox = sf::FloatRect(position, size);
}

void Button::setPosition(sf::Vector2f position) {
    sf::Vector2f size = body.getSize();
    text.setPosition(position.x+size.x/2, position.y+size.y/2);
    body.setPosition(position);
    hitbox = sf::FloatRect(position, size);
}

void Button::resetOrigin() {
    sf::FloatRect bound = text.getLocalBounds();
    text.setOrigin(bound.left+bound.width/2, bound.top+bound.height/2);
}

void Button::setString(std::string string) {
    text.setString(string);
}

sf::Vector2f Button::getPosition() {
    return body.getPosition();
}

bool Button::contains(sf::Vector2f point) {
    return hitbox.contains(point);
}

void Button::press() {
    if (action && buttonTimer.getElapsedTime().asSeconds() > 0.5) {
        this->action();
        buttonTimer.restart();
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(body);
    window.draw(text);
}