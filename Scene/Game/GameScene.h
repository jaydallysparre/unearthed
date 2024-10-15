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
#include <random>

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
    sf::View gameCamera;
    sf::View uiView;
    Entity** enemies;
    int enemyCount = 0;
    int enemyCapacity = 10;
    int maxEnemyCapacity = 40;
    std::vector<sf::Texture> textures;
    std::vector<Interactable*> interactables;
    BulletManager bulletManager;
    sf::Clock directorTimer; 
    sf::Clock gameTimer;
    HUD hud;
    std::mt19937 mt{std::random_device{}()}; // for randomness

    // Remove entity from array
    void killEntity(int idx);

    // So that we only load enemy textures once
    void loadEnemyTexture();

    // Removes interactable from the stage
    void removeInteractable(int idx);
public:
    GameScene(sf::RenderWindow* window, Level level);
    ~GameScene();

    // Add objects to the stage
    void addPlayer(Entity* player);
    void addEnemy(Entity* enemy);
    void addInteractable(Interactable* interactable);
    
    // Sends an alert to the hud
    void sendHudAlert(Alert alert);

    // Upgrade random enemy in enemy array
    void upgradeRandomEnemy();

    // Set director
    void setDirector(Director* director);

    // Have we hit the enemy limit?
    bool isMaxCapacity();

    // Getters
    Level* getLevel();
    Entity* getPlayer();
    BulletManager* getBulletManager();
    sf::Clock getGameTimer();
    std::vector<sf::Texture>* getTextures();
    int getClosestValidInteractable(); // gets the closest valid interactable to the player

    void handleEvent(sf::Event event); 
    void update(float dt);
    void draw();
};

#endif