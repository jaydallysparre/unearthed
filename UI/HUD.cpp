#include "HUD.h"
#include <iostream>

HUD::HUD() {
    if (!font.loadFromFile("Font/Pixellari.ttf")) {
        std::cerr << "Font could not be loaded" << '\n';
    }
    alertText.setFont(font);
    alertText.setPosition(2,2);
    alertText.setCharacterSize(24);
    alertText.setFillColor(sf::Color::White);
    healthbarText.setFont(font);
    healthbarText.setCharacterSize(16);
    healthbarText.setFillColor(sf::Color::White);
    healthbar = new Healthbar(1.4, sf::Vector2f(0,0));
}

HUD::~HUD() {
    delete healthbar;
}

void HUD::addAlert(Alert alert) {
    alerts.emplace(alert);
}

void HUD::drawHUD(int playerHealth, int playerMaxHealth, int money, sf::RenderWindow& window) {
    std::cout << alerts.size() << '\n';
    if (!alerts.empty()) {
        alertText.setString(alerts.top().getText());
        alertText.setOrigin(sf::Vector2f(alertText.getLocalBounds().width/2, alertText.getLocalBounds().height/2));
        if (alertTimer.getElapsedTime().asSeconds() > alerts.top().getTime()) {
            alerts.pop();
            alertTimer.restart();
        }
    }  else {
        alertText.setString("");
    }

    float healthFactor = (float)playerHealth/playerMaxHealth;

    healthbarText.setString(std::to_string(playerHealth) + "/" + std::to_string(playerMaxHealth));

    alertText.setPosition(window.getSize().x/2, window.getSize().y-40);
    healthbarText.setOrigin(sf::Vector2f(healthbarText.getLocalBounds().width/2, healthbarText.getLocalBounds().height/2));
    healthbarText.setPosition(10+(healthbar->getSize().x/2), window.getSize().y-44+(healthbar->getSize().y/2));
    window.draw(alertText);
    healthbar->draw(window.mapPixelToCoords(sf::Vector2i(10,window.getSize().y-40)), healthFactor, window);
    window.draw(healthbarText);
}