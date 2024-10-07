#include "Button.h"

Button::Button(std::string txt, sf::Vector2f position, sf::Font& font) {
    text.setFont(font);
    text.setString(txt);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
}

bool Button::contains(sf::Vector2f point) {
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(body);
    window.draw(text);
}