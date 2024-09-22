#include "SceneManager.h"

SceneManager::SceneManager(Scene* scene) : currentScene(scene) {}

void SceneManager::switchScene(Scene* scene) {
    currentScene = scene;
}

void SceneManager::handleEvents(sf::RenderWindow& window, sf::Event event) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        currentScene->handleEvent(event);
    }
}

void SceneManager::runScene(float dt) {
    currentScene->update(dt);
    currentScene->draw();
}