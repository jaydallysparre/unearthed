#include "HUD.h"

HUD::HUD() {
    healthbar = new Healthbar(1.4, sf::Vector2f(0,0));
}

HUD::~HUD() {
    delete healthbar;
}

#include <iostream>

void HUD::drawHUD(float healthFactor, int money, sf::RenderWindow& window) {
    healthbar->draw(window.mapPixelToCoords(sf::Vector2i(10,window.getSize().y-40)), healthFactor, window);
    
}