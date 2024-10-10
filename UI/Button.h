#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button {
private:
    std::function<void()> action; // stores function to be triggered when button is pressed
    sf::RectangleShape body;
    sf::FloatRect hitbox;
    sf::Text text;
    sf::Clock buttonTimer;
public:
    Button(std::string text, sf::Vector2f position, sf::Vector2f size, sf::Font* font, std::function<void()> action);
    void setPosition(sf::Vector2f position);
    void setString(std::string string);
    void resetOrigin();
    sf::Vector2f getPosition();
    bool contains(sf::Vector2f point);
    void press();
    void draw(sf::RenderWindow& window);
};
#endif