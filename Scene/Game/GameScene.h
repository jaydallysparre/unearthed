#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "MenuScene.h"
#include "Level.h"
#include "Entity.h"
#include "BulletManager.h"
#include "Director.h"
#include "HUD.h"
#include "Interactable.h"
#include "Alert.h"

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
    std::vector<Interactable*> interactables;
    //std::vector<> worldItems;
    BulletManager bulletManager;
    sf::Clock directorTimer; 
    sf::Clock gameTimer;
    HUD hud;
public:
    GameScene(sf::RenderWindow* window, Level level);
    ~GameScene();
    BulletManager* getBulletManager();
    void addPlayer(Entity* player);
    void addEnemy(Entity* enemy);
    void addInteractable(Interactable* interactable);
    void sendHudAlert(Alert alert);
    void killEntity(int idx);
    void removeInteractable(int idx);

    void setDirector(Director* director);
    Level* getLevel();
    Entity* getPlayer();
    sf::Clock getGameTimer();
    int getClosestValidInteractable(); // gets the closest valid interactable to the player

    void handleEvent(sf::Event event); 
    void update(float dt);
    void draw();
};

#endif