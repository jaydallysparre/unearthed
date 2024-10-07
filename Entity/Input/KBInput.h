#ifndef KBINPUT_H
#define KBINPUT_H

#include "InputHandler.h"
#include "MathUtil.h"

class KBInput : public InputHandler {
public:
    void handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window);
};

#endif