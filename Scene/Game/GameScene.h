#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Level.h"
#include "Entity.h"
#include "BulletManager.h"
#include "Director.h"
#include "HUD.h"

class Director;

class GameScene : public Scene {
private:
    Level level;
    Entity* player;
    Director* director;
    int playerMoney = 0;
    sf::View gameCamera;
    sf::View uiView;
    std::vector<Entity*> entities;
    BulletManager bulletManager;
    sf::Clock directorTimer; 
    HUD hud;
public:
    GameScene(sf::RenderWindow* window, Level level);
    ~GameScene();
    BulletManager* getBulletManager();
    void addPlayer(Entity* player);
    void addEnemy(Entity* enemy);
    void killEntity(int idx);

    void setDirector(Director* director);
    Level* getLevel();
    Entity* getPlayer();

    void handleEvent(sf::Event event); 
    void update(float dt);
    void draw();
};

#endif