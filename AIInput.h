#ifndef AIINPUT_H
#define AIINPUT_H

#include "InputHandler.h"

class AIInput : public InputHandler {
public:
    void handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window);
};

#endif