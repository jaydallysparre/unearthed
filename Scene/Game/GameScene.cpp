#include "GameScene.h"
#include "AIInput.h"
#include "HighscoreScene.h"
#include <stack>

GameScene::GameScene(sf::RenderWindow* window, Level level) :Scene(window), level(level) {
    gameCamera = window->getView();
    uiView = window->getView();
    gameCamera.zoom(0.75);
    loadEnemyTexture();
    director = new Director(this);
    director->populateStage();
    loadEnemyTexture();
    enemies = new Entity*[enemyCapacity];
}

GameScene::~GameScene() {
    delete player;

    for (int i = 0; i < enemyCount; ++i) {
        delete enemies[i];
    }
    delete[] enemies;

    for (Interactable* i: interactables) {
        delete i;
    }
    delete director;
}

// The below function is so that enemies can share the same texture for the class.
void GameScene::loadEnemyTexture() {
    sf::Texture t;
    std::vector<std::string> texturesToOpen = {"img/ghost.png"};
    for (int i = 0; i < texturesToOpen.size(); ++i) {
        sf::Texture t;
        t.loadFromFile(texturesToOpen[i]);
        textures.push_back(t);
    }
}

void GameScene::addPlayer(Entity* player) {
    this->player = player;
}

void GameScene::addEnemy(Entity* enemy) {
    if (enemyCount + 1 <= enemyCapacity) {
        enemies[enemyCount++] = enemy;
    }
    else if (enemyCapacity + 10 <= maxEnemyCapacity) {
        Entity** temp = new Entity*[enemyCapacity+10];
        for (int i = 0; i < enemyCapacity; ++i) {
            temp[i] = enemies[i];
        }
        delete[] enemies;
        enemies = temp;
        enemyCapacity += 10;
        enemies[enemyCount++] = enemy;
    }
    else {
        std::cerr << "Tried to spawn enemy past capacity\n";
        delete enemy;
    }
}

bool GameScene::isMaxCapacity() {
    return enemyCount == maxEnemyCapacity;
}

void GameScene::addInteractable(Interactable* interactable) {
    interactables.push_back(interactable);
}

void GameScene::sendHudAlert(Alert alert) {
    hud.addAlert(alert);
}

void GameScene::killEntity(int idx) {

    delete enemies[idx];

    // shuffle enemies back
    for (int i = idx; i < enemyCount-1; ++i) {
        enemies[i] = enemies[i+1];
    }
    enemyCount--;
}

void GameScene::removeInteractable(int idx) {
    delete interactables[idx];
    interactables.erase(interactables.begin() + idx);
}

void GameScene::upgradeRandomEnemy() {
    std::uniform_int_distribution randomEnemy{0, enemyCount};
    std::uniform_int_distribution randomUpgrade(1, 3);
    Entity* enemy = enemies[randomEnemy(mt)];
    switch (randomUpgrade(mt)) {
        case 1:
            enemy->upgradeAttackSpeed(0.05);
            break;
        case 2:
            enemy->upgradeAttackDamage(10);
            break;
        case 3:
            enemy->upgradeSpeed(10);
            break;
    }
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

sf::Clock GameScene::getGameTimer() {
    return gameTimer;
}

std::vector<sf::Texture>* GameScene::getTextures() {
    return &textures;
}


int GameScene::getClosestValidInteractable() {
    float distance = std::numeric_limits<float>::infinity();
    int idx = -1;
    for (int i = 0; i < interactables.size(); ++i) {
        interactables[i]->setHighlight(false);
        float currentDistance = MathUtil<sf::Vector2f>::distance(interactables[i]->getPosition(), player->getPosition());
        if (currentDistance < 50 && currentDistance < distance) {
            distance = currentDistance;
            idx = i;
            interactables[i]->setHighlight(true);
            if (!hud.currentAlertIsHighPriority()) {
                hud.addAlert(Alert("Chest: Click E to open.", 0, 1));
            }
        }
    }
    return idx;
}

void GameScene::handleEvent(sf::Event event) {
    if (event.type == sf::Event::Resized) {
        gameCamera = sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height));
        uiView = sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height));
        gameCamera.zoom(0.75);  
    }
}

void GameScene::update(float dt) {
    if (player->isDead()) { // Finish the game!
        transitionScene = new HighScoreScene(window, true, gameTimer.getElapsedTime().asSeconds());
        return;
    }
    // Go to the menu if escape is pressed
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
    for (int i = 0; i < enemyCount; ++i) {
        enemies[i]->update(*window, level, dt);
        if (enemies[i]->isDead()) {
            killEntity(i);
        }
    }
    // Interactable use logic
    int closestInteractableIdx = getClosestValidInteractable();
    if ((closestInteractableIdx != -1) && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        hud.addAlert(interactables[closestInteractableIdx]->use(player));
        removeInteractable(closestInteractableIdx);
    }
    bulletManager.update(level, enemies, enemyCount, player, dt);
}

void GameScene::draw() {
    window->setView(gameCamera);
    level.display(*window);
    bulletManager.display(*window);

    for (int i = 0; i < enemyCount; ++i) {
        // If we are debugging, show the paths the enemy AI finds
        if (debug) {
            InputHandler* IH = enemies[i]->getInputHandler();
            std::stack<AINode*> nodePath = static_cast<AIInput*>(IH)->getNodePath();
            while (!nodePath.empty()) {
                sf::CircleShape shape(1);
                shape.setPosition(sf::Vector2f(nodePath.top()->x*32+16, nodePath.top()->y*32+16));
                window->draw(shape);
                nodePath.pop();
            }
        }
        enemies[i]->display(*window);
    }

    for (Interactable* interactable : interactables) {
        interactable->display(*window);
    }
    player->display(*window);
    window->setView(uiView);
    hud.drawHUD(player->getHealth(), player->getMaxHealth(), gameTimer.getElapsedTime().asSeconds(), *window);
}

