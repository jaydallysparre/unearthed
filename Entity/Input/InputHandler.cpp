#include "InputHandler.h"

InputHandler::InputHandler() {}

bool InputHandler::isMoving() {
    return move;
}

bool InputHandler::isAttacking() {
    return attack;
}

sf::Vector2f InputHandler::getMoveDir() {
    return moveDir;
}

sf::Vector2f InputHandler::getAttackDir() {
    return attackDir;
}
