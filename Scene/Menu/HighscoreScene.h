#ifndef HIGHSCORE_SCENE
#define HIGHSCORE_SCENE

#include "Scene.h"
#include "Button.h"
#include <utility>
#include <string>

class HighScoreScene : public Scene {
private:
    sf::Font font;
    sf::Text gameEndText; // Whether a new highscore was gotten or not
    sf::Text highscoreText; // Current highscore
    bool edit;
    bool getName = false;
    // highscore variables, for use if the player gets a new highscore
    int hs;
    std::string name;
public:
    HighScoreScene(sf::RenderWindow* window, bool edit, int score=0);
    void handleEvent(sf::Event event);
    std::pair<int, std::string> loadHighScore();
    void setHighScore();
    void update(float dt);
    void draw();
};

#endif