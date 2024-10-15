#ifndef KBINPUT_H
#define KBINPUT_H

#include "InputHandler.h"
#include "MathUtil.h"

/*
* Input handler for keyboard only input.
*/

class KBInput : public InputHandler {
public:
    // Sets attributes based on keyboard only input
    void handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window);
};

#endif