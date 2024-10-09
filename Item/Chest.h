#ifndef CHEST_H
#define CHEST_H

#include "Interactable.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Chest : public Interactable {
public:
    Chest(sf::Vector2f position);
    void setHighlight(bool highlight);
    Alert use(Entity* entity);
};

#endif