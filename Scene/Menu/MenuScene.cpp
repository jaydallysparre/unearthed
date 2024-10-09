#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene(sf::RenderWindow* window) : Scene(window) {
    font = new sf::Font;
    if (!font->loadFromFile("Font/Pixellari.ttf")) {
        std::cerr << "Font could not be loaded" << '\n';
    }
    buttons.push_back(Button("Start Game", sf::Vector2f(window->getSize().x/2 - 100,200), sf::Vector2f(200,50), font, [this]{startGame();}));
    buttons.push_back(Button("Exit", sf::Vector2f(window->getSize().x/2-100,270), sf::Vector2f(200,50), font, [window]{window->close();}));
}

MenuScene::~MenuScene() {
    delete font;
}

void MenuScene::startGame() {
    GameScene* game = new GameScene(window, Level("level1.txt", "level1.png", 32, {2}, {EnemyType::Enemy::Ghost}));
    InputHandler* input;
    switch(inputType) {
        case KB:
            input = new KBInput();
            break;
        case KBM:
            input = new KBMInput();
            break;
        default:
            input = new KBMInput();
    }
    Entity* player = new Commando(input, sf::Vector2f(64.f, 64.f), Team::ALLY, game->getBulletManager());
    game->addPlayer(player);
    transitionScene = game;
}

void MenuScene::handleEvent(sf::Event event) {
    if (event.type == sf::Event::Resized) {
        window->setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
        for (Button& button : buttons) {
            button.setPosition(sf::Vector2f(window->getSize().x/2-100, button.getPosition().y));
        }
    }
}

void MenuScene::update(float dt) {
    for (Button& button : buttons) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button.contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window), window->getView()))) {
            button.press();
        }
    }
}

void MenuScene::draw() {
    for (Button button : buttons) {
        button.draw(*window);
    }
}