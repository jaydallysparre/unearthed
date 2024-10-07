#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

class Scene {
protected:
    sf::RenderWindow* window;
    Scene* transitionScene = nullptr;
public:
    Scene(sf::RenderWindow* window) : window(window) {}
    virtual ~Scene() = default;
    virtual void handleEvent(sf::Event event) = 0;
    Scene* getTransitionScene() {return transitionScene;};
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
};

#endif