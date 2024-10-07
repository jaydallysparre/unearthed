#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"
#include "Button.h"
#include <vector>

class MenuScene : public Scene {
private:
    std::vector<Button> buttons;
public:
    MenuScene(sf::RenderWindow* window);
    ~MenuScene();
    void handleEvent(sf::Event event);
    void update(float dt);
    void draw();
};

#endif