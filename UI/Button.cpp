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
    body.setFillColor(sf::Color::Blue);
    hitbox = sf::FloatRect(position, size);
}

void Button::setPosition(sf::Vector2f position) {
    std::cout << "position set to " << position.x << "," << position.y << '\n';
    sf::Vector2f size = body.getSize();
    text.setPosition(position.x+size.x/2, position.y+size.y/2);
    body.setPosition(position);
    hitbox = sf::FloatRect(position, size);
}

sf::Vector2f Button::getPosition() {
    return body.getPosition();
}

bool Button::contains(sf::Vector2f point) {
    return hitbox.contains(point);
}

void Button::press() {
    if (action) {
        this->action();
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(body);
    window.draw(text);
}