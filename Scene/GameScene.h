#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Level.h"
#include "Entity.h"
#include "BulletManager.h"

class GameScene : public Scene {
private:
    Level level;
    Entity* player;
    int playerMoney = 0;
    sf::View gameCamera;
    std::vector<Entity*> entities;
    BulletManager bulletManager;
public:
    GameScene(sf::RenderWindow* window, Level level);
    ~GameScene();
    BulletManager* getBulletManager();
    Level* getLevel();
    void addPlayer(Entity* player);
    void addEnemy(Entity* enemy);
    void killEntity(int idx);
    void handleEvent(sf::Event event); 
    void update(float dt);
    void draw();
};

#endif