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

class Director; // Forward declaration as they rely on eachother

/*
* In charge of the game logic past the menu.
*/

class GameScene : public Scene {
private:
    bool debug = false;
    Level level;
    Entity* player;
    Director* director;
    int playerMoney = 0;
    sf::View gameCamera;
    sf::View uiView;
    std::vector<Entity*> entities;
    std::vector<sf::Texture> textures;
    std::vector<Interactable*> interactables;
    BulletManager bulletManager;
    sf::Clock directorTimer; 
    sf::Clock gameTimer;
    HUD hud;
public:
    GameScene(sf::RenderWindow* window, Level level);
    ~GameScene();
    void loadEnemyTexture();
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
    std::vector<sf::Texture>* getTextures();
    int getClosestValidInteractable(); // gets the closest valid interactable to the player

    void handleEvent(sf::Event event); 
    void update(float dt);
    void draw();
};

#endif