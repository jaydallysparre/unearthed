#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

/*
* Healthbar class, to visually display the health of entities
*/

class Healthbar {
    sf::RectangleShape shell;
public:
    Healthbar(float scale, sf::Vector2f position);
    sf::Vector2f getSize();
    void draw(sf::Vector2f position, float healthpercentage, sf::RenderWindow& window);
};

#endif