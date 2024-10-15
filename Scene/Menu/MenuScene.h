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

/*
* Main menu scene.
*/

class MenuScene : public Scene {
private:
    enum Input {
        KB,
        KBM
    };
    std::vector<Button> buttons;
    sf::Font* font;
    Input inputType = KBM;
    int buttonWidth = 300;
    sf::Texture menuTitleTexture;
    sf::Sprite menuTitle;
    std::string toggleInputType();
    void startGame();
public:
    MenuScene(sf::RenderWindow* window);
    ~MenuScene();
    void handleEvent(sf::Event event);
    void update(float dt);
    void draw();
};

#endif