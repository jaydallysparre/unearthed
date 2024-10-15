#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <SFML/Graphics.hpp>
#include "Alert.h"
#include "Entity.h"

/*
* Base interactable class. Exist as physical things in the gamescene the player can interact with
*/

class Interactable {
protected:
    sf::Texture spriteTexture;
    sf::Texture highlightTexture;
    sf::Sprite sprite;
public:
    Interactable(sf::Vector2f position) {
        sprite.setPosition(position);
    }
    virtual ~Interactable() {};
    
    sf::Vector2f getPosition() {
        return sprite.getPosition();
    }

    // Set the highlight texture. Player knows interactable is targeted this way
    virtual void setHighlight(bool highlight) = 0;

    // Have an effect when used by argument entity
    virtual Alert use(Entity* entity) = 0;

    // Draw on the map
    void display(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

#endif