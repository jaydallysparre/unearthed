#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Level.h"
#include "KBMInput.h"
#include "AIInput.h"
#include "Commando.h"
#include "Ghost.h"
#include "SceneManager.h"
#include "GameScene.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "SFML Project");
    sf::Clock deltaClock;

    GameScene* game = new GameScene(&window, Level("level1.txt", "level1.png", 32, {2}));
    Entity* player = new Commando(new KBMInput(), sf::Vector2f(64.f, 64.f), Team::ALLY, game->getBulletManager());
    Entity* enemy = new Ghost(new AIInput(player, game->getLevel()), sf::Vector2f(128.f, 128.f), Team::ENEMY, game->getBulletManager());
    game->addPlayer(player);
    game->addEnemy(enemy);
    SceneManager sceneManager(game);

    while (window.isOpen()) {
        // Handle SFML events (closing game, resizing window, etc)
        float dt = deltaClock.restart().asSeconds();
        sf::Event event;
        sceneManager.handleEvents(window, event);

        // Update and display scene
        sceneManager.runScene(dt);
        window.clear(sf::Color(22, 20, 26));
        sceneManager.drawScene();
        window.display();
    }
    return 0;
}
