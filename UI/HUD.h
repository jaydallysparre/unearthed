#ifndef HUD_H
#define HUD_H

#include "Healthbar.h"
#include "Alert.h"
#include <queue>

/*
* HUD, or heads up display has UI for the player to see during gameplay
*/

class HUD {
private:
    Healthbar* healthbar;
    sf::Font font;
    std::priority_queue<Alert, std::vector<Alert>, std::greater<Alert>> alerts;
    sf::Text alertText;
    sf::Clock alertTimer;
    sf::Text healthbarText;
    sf::Text timeText;
public:
    HUD();
    ~HUD();
    void addAlert(Alert alert);
    bool currentAlertIsHighPriority(); // Low priority messages can avoid being added to the queue
    void drawHUD(int playerHealth, int playerMaxHealth, int time, sf::RenderWindow& window);
};

#endif