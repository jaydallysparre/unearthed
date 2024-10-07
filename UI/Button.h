#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape body;
    sf::Text text;
public:
    Button(std::string text, sf::Vector2f position, sf::Font& font);
    bool contains(sf::Vector2f point);
    void draw(sf::RenderWindow& window);
};
#endif