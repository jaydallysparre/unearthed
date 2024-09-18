#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Level.h"
#include "KBMInput.h"
#include "Entity.h"

class Commando : public Entity {
public:
    Commando(InputHandler* inputHandler, sf::Vector2f spawnPos, Team team) : Entity(inputHandler, spawnPos, team) {
        spriteTexture.loadFromFile("commando_idle.png");
        sprite.setTexture(spriteTexture);
        sprite.setHitbox({8.f, 0.f, 16.f, 32.f});
        speed = 150;
        health = 300;
    }
    void attack(sf::Vector2i attackDir) {
        //
    }
    void takeDamage(int dmgAmount) {
        //
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML");
    Level level("level1.txt", "level1.png", 32, {2});
    KBMInput playerInput;
    sf::Vector2f spawnPos(64.f, 64.f);
    Commando player(&playerInput, spawnPos, Team::ALLY);
    sf::View view = window.getDefaultView();
    window.setView(view);
    sf::Clock deltaClock;
    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear();
        view.setCenter(player.getPosition().x, player.getPosition().y);
        window.setView(view);
        level.display(window);
        player.update(window, level, dt);
        window.display();
    }
    return 0;
}