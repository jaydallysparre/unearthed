#include "MenuScene.h"

MenuScene::MenuScene(sf::RenderWindow* window) : Scene(window) {
    sf::Font font;
    if (!font.loadFromFile("Font/Pixellari.ttf")) {
        std::cerr << "Font could not be loaded" << '\n';
    }
    buttons.push_back(Button("Start Game", sf::Vector2f(0,0)), font);
}

MenuScene::~MenuScene() {
    //
}

void MenuScene::handleEvent(sf::Event event) {

}

void MenuScene::update(float dt) {

}

void MenuScene::draw() {
    for (Button button : buttons) {
        button.draw(window);
    }
}