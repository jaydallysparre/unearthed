#include "InputHandler.h"

bool InputHandler::isMoving() {
    return move;
}

bool InputHandler::isAttacking() {
    return attack;
}

bool InputHandler::isSpecialing() {
    return special;
}

sf::Vector2f InputHandler::getMoveDir() {
    return moveDir;
}

sf::Vector2f InputHandler::getAttackDir() {
    return attackDir;
}
