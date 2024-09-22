#include "HBSprite.h"

void HBSprite::setHitbox(const sf::FloatRect& hitbox) {
    this->hitbox = hitbox;
}

sf::FloatRect HBSprite::getGlobalHitbox() const {
    return getTransform().transformRect(hitbox);
}