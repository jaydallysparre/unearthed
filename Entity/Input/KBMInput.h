#ifndef KBMINPUT_H
#define KBMINPUT_H

#include "InputHandler.h"
#include "MathUtil.h"

/*
* Input handler for keyboard and mouse input.
*/

class KBMInput : public InputHandler {
public:
    // sets attributes based on keyboard and mouse input
    void handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window);
};

#endif