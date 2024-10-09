#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

class Scene {
protected:
    sf::RenderWindow* window;
    Scene* transitionScene = nullptr;
public:
    Scene(sf::RenderWindow* window) : window(window) {
        window->setView(sf::View(sf::FloatRect(0.f, 0.f, window->getSize().x, window->getSize().y))); // reset view changes by gamescene, if any
    }
    virtual ~Scene() = default;
    virtual void handleEvent(sf::Event event) = 0;
    Scene* getTransitionScene() {return transitionScene;};
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
};

#endif