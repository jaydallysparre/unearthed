#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Graphics.hpp>

/*
Abstract class to handle inputs. This is useful so inputs and entities can be decoupled.
*/

class InputHandler {
protected:
    bool move;
    bool attack;
    sf::Vector2f moveDir;
    sf::Vector2f attackDir;
public:
    InputHandler();

    // function designed to set attributes for entity to read
    void virtual handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window) = 0;

    // Return directions
    sf::Vector2f getMoveDir();
    sf::Vector2f getAttackDir();

    // Return states
    bool isMoving();
    bool isAttacking();
};

#endif