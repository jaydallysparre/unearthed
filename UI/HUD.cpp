#include "HUD.h"
#include <iostream>
#include <sstream>
#include <iomanip>

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
    timeText.setFont(font);
    timeText.setCharacterSize(40);
    timeText.setFillColor(sf::Color::White);
    healthbar = new Healthbar(1.4, sf::Vector2f(0,0));
}

HUD::~HUD() {
    delete healthbar;
}

void HUD::addAlert(Alert alert) {
    alerts.emplace(alert);
}

bool HUD::currentAlertIsHighPriority() {
    if (alerts.empty()) {
        return false;
    }
    return alerts.top().getPriority() == 0;
}

void HUD::drawHUD(int playerHealth, int playerMaxHealth, int time, sf::RenderWindow& window) {
    // Handle and draw alerts
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
    alertText.setPosition(window.getSize().x/2, window.getSize().y-40);
    window.draw(alertText);

    // Handle and draw health
    float healthFactor = (float)playerHealth/playerMaxHealth;
    healthbarText.setString(std::to_string(playerHealth) + "/" + std::to_string(playerMaxHealth));
    healthbarText.setOrigin(sf::Vector2f(healthbarText.getLocalBounds().width/2, healthbarText.getLocalBounds().height/2));
    healthbarText.setPosition(10+(healthbar->getSize().x/2), window.getSize().y-44+(healthbar->getSize().y/2));
    healthbar->draw(window.mapPixelToCoords(sf::Vector2i(10,window.getSize().y-40)), healthFactor, window);
    window.draw(healthbarText);

    // Handle and draw time
    std::stringstream minutes;
    std::stringstream seconds;
    minutes << std::setfill('0') << std::setw(2) << time/60;
    seconds << std::setfill('0') << std::setw(2) << time % 60;
    timeText.setString(minutes.str() + ":" + seconds.str());
    timeText.setOrigin(timeText.getLocalBounds().width/2,0);
    timeText.setPosition(window.getSize().x/2,2);
    window.draw(timeText);
}