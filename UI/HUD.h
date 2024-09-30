#ifndef HUD_H
#define HUD_H

#include "Healthbar.h"

class HUD {
private:
    Healthbar* healthbar;
public:
    HUD();
    ~HUD();
    void drawHUD(float healthFactor, int money, sf::RenderWindow& window);
};

#endif