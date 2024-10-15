#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

/*
* Button on the screen, which stores a function to be triggered when clicked
*/

class Button {
private:
    std::function<void()> action; // stores function to be triggered when button is pressed
    sf::RectangleShape body;
    sf::FloatRect hitbox;
    sf::Text text;
    sf::Clock buttonTimer;
public:
    Button(std::string text, sf::Vector2f position, sf::Vector2f size, sf::Font* font, std::function<void()> action);

    // Setters
    void setPosition(sf::Vector2f position);
    void setString(std::string string);

    // Reset origin of the button
    void resetOrigin();

    // Get position of the button
    sf::Vector2f getPosition();

    // Does the button contain a point? Used for mouse clicking
    bool contains(sf::Vector2f point);

    // Do callable stored in action
    void press();

    // Draw the button
    void draw(sf::RenderWindow& window);
};
#endif