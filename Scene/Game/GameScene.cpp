#include "GameScene.h"
#include "AIInput.h"
#include <stack>

GameScene::GameScene(sf::RenderWindow* window, Level level) :Scene(window), level(level) {
    gameCamera = window->getDefaultView();
    director = new Director(this);
}

GameScene::~GameScene() {
    delete player;
    for (Entity* e: entities) {
        delete e;
    }
    delete director;
}

void GameScene::addPlayer(Entity* player) {
    this->player = player;
}

void GameScene::addEnemy(Entity* enemy) {
    entities.push_back(enemy);
}

void GameScene::killEntity(int idx) {
    playerMoney += entities[idx]->getValue();
    delete entities[idx];
    entities.erase(entities.begin() + idx);
}

BulletManager* GameScene::getBulletManager() {
return &bulletManager;
}

Level* GameScene::getLevel() {
    return &level;
}

Entity* GameScene::getPlayer() {
    return player;
}

void GameScene::handleEvent(sf::Event event) {
    if (event.type == sf::Event::Resized) {
        gameCamera = sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height));
        uiView = sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height));
        gameCamera.zoom(0.75);  
    }
}

void GameScene::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        transitionScene = new MenuScene(window);
        return;
    }
    window->setView(gameCamera); // player input relies on view being set
    gameCamera.setCenter(player->getOrigin());
    player->update(*window, level, dt);
    if (directorTimer.getElapsedTime().asSeconds() > 1) {
        director->update();
        directorTimer.restart();
    }
    for (int i = 0; i < entities.size(); ++i) {
        entities[i]->update(*window, level, dt);
        if (entities[i]->isDead()) {
            killEntity(i);
        }
    }
    bulletManager.update(level, entities, player, dt);
}

void GameScene::draw() {
    window->setView(gameCamera);
    level.display(*window);
    bulletManager.display(*window);
    for (Entity* entity: entities) {
        InputHandler* IH = entity->getInputHandler();
        std::stack<AINode*> nodePath = static_cast<AIInput*>(IH)->getNodePath();
        while (!nodePath.empty()) {
            sf::CircleShape shape(1);
            shape.setPosition(sf::Vector2f(nodePath.top()->x*32+16, nodePath.top()->y*32+16));
            window->draw(shape);
            nodePath.pop();
        }
        entity->display(*window);
    }
    player->display(*window);
    window->setView(uiView);
    hud.drawHUD((float)player->getHealth()/player->getMaxHealth(), playerMoney, *window);
}

