#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"

class SceneManager {
private:
    Scene* currentScene;
    void switchScene(Scene* scene);
public:
    SceneManager(Scene* scene);
    ~SceneManager();
    void handleEvents(sf::RenderWindow& window, sf::Event event);
    void runScene(float dt); 
    void drawScene();
};

#endif