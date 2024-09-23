#ifndef AIINPUT_H
#define AIINPUT_H

#include "InputHandler.h"
#include "Entity.h"

class AIInput : public InputHandler {
    Entity* target; // Player to target
public:
    AIInput(Entity* player);
    void handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window);
};

#endif