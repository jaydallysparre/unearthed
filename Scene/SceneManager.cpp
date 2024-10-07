#include "SceneManager.h"

SceneManager::SceneManager(Scene* scene) : currentScene(scene) {}

SceneManager::~SceneManager() {
    delete currentScene;
}

void SceneManager::switchScene(Scene* scene) {
    delete currentScene;
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
    if (currentScene->getTransitionScene()) { // change schene if currentScene creates a transition scene
        switchScene(currentScene->getTransitionScene());
    }
}

void SceneManager::drawScene() {
    currentScene->draw();
}