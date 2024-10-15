#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"

class SceneManager {
private:
    Scene* currentScene;
    
    // Deallocate previous scene and switch to new scene
    void switchScene(Scene* scene);
public:
    SceneManager(Scene* scene);
    ~SceneManager();

    // Handle SFML events
    void handleEvents(sf::RenderWindow& window, sf::Event event);

    // Run the scene logic
    void runScene(float dt); 

    // Draw the scene
    void drawScene();
};

#endif