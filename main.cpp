#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Level.h"
#include "KBMInput.h"
#include "KBInput.h"
#include "AIInput.h"
#include "Commando.h"
#include "Ghost.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "HighscoreScene.h"
#include "EnemyType.h"

int main() {
    Level level("data/level1.txt", "img/level1.png", 32, {2}, {EnemyType::Enemy::Ghost}); 
    sf::RenderWindow window(sf::VideoMode(800,600), "unearthed.");
    sf::Clock deltaClock;
    MenuScene* menu = new MenuScene(&window);
    SceneManager sceneManager(menu);

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
