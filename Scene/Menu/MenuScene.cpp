#include "MenuScene.h"
#include "HighscoreScene.h"
#include <iostream>

MenuScene::MenuScene(sf::RenderWindow* window) : Scene(window) {
    font = new sf::Font;
    if (!font->loadFromFile("Font/Pixellari.ttf")) {
        std::cerr << "Font could not be loaded" << '\n';
    }

    if (!menuTitleTexture.loadFromFile("img/unearthed.png")) {
        std::cerr << "Image could not be loaded" << '\n';
    }

    sf::Vector2f windowCenter = window->getView().getCenter();

    menuTitle.setTexture(menuTitleTexture);
    menuTitle.setOrigin(menuTitle.getLocalBounds().width/2, 0);
    menuTitle.setPosition(windowCenter.x,0);
    // Adding buttons to the screen. Buttons functions are passed through the constructor as lambda expressions.
    int buttonStart = 230;
    buttons.push_back(Button("Start Game", sf::Vector2f(windowCenter.x-buttonWidth/2,buttonStart), sf::Vector2f(buttonWidth,70), font, [this] {
        startGame();
    }));
    buttons.push_back(Button("Input Type", sf::Vector2f(windowCenter.x-buttonWidth/2,buttonStart+90), sf::Vector2f(buttonWidth,70), font, [this] {
        this->buttons[1].setString(toggleInputType());
        this->buttons[1].resetOrigin();
    }));
    buttons.push_back(Button("Highscore", sf::Vector2f(windowCenter.x-buttonWidth/2,buttonStart+2*90), sf::Vector2f(buttonWidth,70), font, [window, this]{
        transitionScene = new HighScoreScene(window, false, 0);
    }));
    buttons.push_back(Button("Exit", sf::Vector2f(windowCenter.x-buttonWidth/2,buttonStart+3*90), sf::Vector2f(buttonWidth,70), font, [window] {
        window->close();
    }));
}

MenuScene::~MenuScene() {
    delete font;
}

void MenuScene::startGame() {
    GameScene* game = new GameScene(window, Level("data/level1.txt", "img/level1.png", 32, {2}, {EnemyType::Enemy::Ghost}));
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

std::string MenuScene::toggleInputType() {
    if (inputType == KBM) {
        inputType = KB;
        return "WASD/ARROW KEYS";
    } else {
        inputType = KBM;
        return "WASD/MOUSE";
    }
}

void MenuScene::handleEvent(sf::Event event) {
    if (event.type == sf::Event::Resized) {
        window->setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
        for (Button& button : buttons) {
            button.setPosition(sf::Vector2f(window->getView().getCenter().x-buttonWidth/2, button.getPosition().y));
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
    menuTitle.setPosition(window->getSize().x/2,0);
    window->draw(menuTitle);
}