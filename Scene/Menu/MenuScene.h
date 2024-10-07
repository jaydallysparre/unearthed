#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "KBInput.h"
#include "KBMInput.h"
#include "Commando.h"
#include <vector>

class MenuScene : public Scene {
private:
    enum Input {
        KB,
        KBM
    };
    std::vector<Button> buttons;
    sf::Font* font;
    Input inputType = KBM;
    
public:
    MenuScene(sf::RenderWindow* window);
    ~MenuScene();
    void startGame();
    void handleEvent(sf::Event event);
    void update(float dt);
    void draw();
};

#endif