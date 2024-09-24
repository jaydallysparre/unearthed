#include "GameScene.h"
#include "AIInput.h"

GameScene::GameScene(sf::RenderWindow* window, Level level) :Scene(window), level(level) {
    gameCamera = window->getDefaultView();
}

GameScene::~GameScene() {
    delete player;
    for (Entity* e: entities) {
        delete e;
    }
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

void GameScene::handleEvent(sf::Event event) {
    if (event.type == sf::Event::Resized) {
        gameCamera = sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height));
        gameCamera.zoom(0.75);  
    }
}

void GameScene::update(float dt) {
    gameCamera.setCenter(player->getOrigin());
    window->setView(gameCamera);
    player->update(*window, level, dt);

    for (int i = 0; i < entities.size(); ++i) {
        entities[i]->update(*window, level, dt);
        if (entities[i]->isDead()) {
            killEntity(i);
        }
    }
    bulletManager.update(level, entities, dt);
}

void GameScene::draw() {
    level.display(*window);
    bulletManager.display(*window);
    for (Entity* entity: entities) {
        InputHandler* IH = entity->getInputHandler();

        for (AINode* n : (static_cast<AIInput*>(IH))->getNodePath()) {
            sf::CircleShape shape(2);
            shape.setPosition(sf::Vector2f(n->x*32+16, n->y*32+16));
            window->draw(shape);
        }
        entity->display(*window);
    }
    player->display(*window);
}

