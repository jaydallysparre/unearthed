#ifndef HBSPRITE_H
#define HBSPRITE_H

#include <SFML/Graphics.hpp>

/*
* Sprite with an attached hitbox.
*/

class HBSprite : public sf::Sprite {
private:
    sf::FloatRect hitbox;
public:
    void setHitbox(const sf::FloatRect& hitbox);
    sf::FloatRect getGlobalHitbox() const;
};

#endif