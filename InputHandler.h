#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Graphics.hpp>

/*
Abstract class to handle inputs. This is useful so inputs and entities can be decoupled.
This will allow for the player to take control of any entity class if desired.
*/

class InputHandler {
protected:
    bool move;
    bool attack;
    bool special;
    sf::Vector2f moveDir;
    sf::Vector2f attackDir;
public:
    void virtual handleInputs(sf::Vector2f entityOrigin, sf::RenderWindow& window) = 0;
    bool isMoving();
    sf::Vector2f getMoveDir();
    sf::Vector2f getAttackDir();
    bool isAttacking();
    bool isSpecialing();
};

#endif