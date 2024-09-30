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
#include "EnemyType.h"

int main() {
    Level level("level1.txt", "level1.png", 32, {2}, {EnemyType::Enemy::Ghost}); 
    sf::RenderWindow window(sf::VideoMode(800,600), "SFML Project");
    sf::Clock deltaClock;

    GameScene* game = new GameScene(&window, Level("level1.txt", "level1.png", 32, {2}, {EnemyType::Enemy::Ghost}));
    Entity* player = new Commando(new KBMInput(), sf::Vector2f(64.f, 64.f), Team::ALLY, game->getBulletManager());
    game->addPlayer(player);
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
