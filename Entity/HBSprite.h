#ifndef HBSPRITE_H
#define HBSPRITE_H

#include <SFML/Graphics.hpp>

class HBSprite : public sf::Sprite {
private:
    sf::FloatRect hitbox;
public:
    void setHitbox(const sf::FloatRect& hitbox);
    sf::FloatRect getGlobalHitbox() const;
};

#endif