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
    sf::Text errorText; // If the user doesn't figure out typing a name
    sf::Clock instructionalDelay; // Work around the error messages
    bool edit;
    bool getName = false;
    // highscore variables, for use if the player gets a new highscore
    int hs;
    std::string name;
    Button* menuReturn;

    std::pair<int, std::string> loadHighScore();
    void setHighScore();
    void returnToMenu();
    std::string formatToMinutes(int seconds);
    bool buttonContainsMouse(Button& button);
public:
    HighScoreScene(sf::RenderWindow* window, bool edit, int score=0);
    ~HighScoreScene();
    void handleEvent(sf::Event event);
    void update(float dt);
    void draw();
};

#endif