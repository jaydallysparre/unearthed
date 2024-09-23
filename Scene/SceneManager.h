#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"

class SceneManager {
private:
    Scene* currentScene;
public:
    SceneManager(Scene* scene);
    void switchScene(Scene* scene);
    void handleEvents(sf::RenderWindow& window, sf::Event event);
    void runScene(float dt); 
    void drawScene();
};

#endif