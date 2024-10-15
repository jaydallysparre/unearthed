#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <SFML/Graphics.hpp>
#include "Alert.h"
#include "Entity.h"

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
    virtual void setHighlight(bool highlight) = 0;
    virtual Alert use(Entity* entity) = 0;
    void display(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

#endif