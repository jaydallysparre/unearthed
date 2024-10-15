#ifndef CHEST_H
#define CHEST_H

#include "Interactable.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>

/*
* Interactable chest class. Gives the player a random stat upgrade upon opening.
*/

class Chest : public Interactable {
public:
    Chest(sf::Vector2f position);

    // Set whether the chest uses its highlighted texture
    void setHighlight(bool highlight);

    // Gives the entity in the argument a random upgrade
    Alert use(Entity* entity);
};

#endif