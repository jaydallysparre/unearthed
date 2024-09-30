#ifndef KBMINPUT_H
#define KBMINPUT_H

#include "InputHandler.h"
#include "MathUtil.h"

class KBMInput : public InputHandler {
public:
    void handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window);
};

#endif