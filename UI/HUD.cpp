#include "HUD.h"
#include <iostream>

HUD::HUD() {
    if (!font.loadFromFile("Font/Pixellari.ttf")) {
        std::cerr << "Font could not be loaded" << '\n';
    }
    alertText.setFont(font);
    alertText.setPosition(2,2);
    alertText.setCharacterSize(16);
    alertText.setFillColor(sf::Color::White);
    healthbar = new Healthbar(1.4, sf::Vector2f(0,0));
}

HUD::~HUD() {
    delete healthbar;
}

void HUD::addAlert(Alert alert) {
    alerts.emplace(alert);
}

void HUD::drawHUD(float healthFactor, int money, sf::RenderWindow& window) {
    std::cout << alerts.size() << '\n';
    if (!alerts.empty()) {
        alertText.setString(alerts.top().getText());
        if (alertTimer.getElapsedTime().asSeconds() > alerts.top().getTime()) {
            alerts.pop();
            alertTimer.restart();
        }
    }  else {
        alertText.setString("");
    }
    window.draw(alertText);
    healthbar->draw(window.mapPixelToCoords(sf::Vector2i(10,window.getSize().y-40)), healthFactor, window);
}