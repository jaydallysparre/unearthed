#ifndef HUD_H
#define HUD_H

#include "Healthbar.h"
#include "Alert.h"
#include <queue>

class HUD {
private:
    Healthbar* healthbar;
    sf::Font font;
    std::priority_queue<Alert, std::vector<Alert>, std::greater<Alert>> alerts;
    sf::Text alertText;
    sf::Clock alertTimer;
public:
    HUD();
    ~HUD();
    void addAlert(Alert alert);
    void drawHUD(float healthFactor, int money, sf::RenderWindow& window);
};

#endif