#include "HighscoreScene.h"
#include "MenuScene.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

HighScoreScene::HighScoreScene(sf::RenderWindow* window, bool edit, int score) : Scene(window), edit(edit), hs(score) {
    window->setView(sf::View(sf::FloatRect(0,0,window->getSize().x,window->getSize().y)));
    if (!font.loadFromFile("Font/Pixellari.ttf")) {
        std::cerr << "Font not found" << '\n';
    }
    std::pair<int, std::string> highscoreData = loadHighScore();
    int highscore = highscoreData.first;
    if (edit) {
        if (score > highscore) {
            gameEndText.setString("New highscore!");
            getName = true;
        } else {
            gameEndText.setString("You didn't beat your highscore :(");
        }
    } else if (highscore == 0) {
        highscoreText.setString("No highscore currently set!");
    }
    if (highscore > 0) {
        highscoreText.setString("Highscore: " + formatToMinutes(highscore) + " by " + highscoreData.second);
    }
    gameEndText.setFont(font);
    gameEndText.setFillColor(sf::Color::White);
    gameEndText.setCharacterSize(30);

    highscoreText.setFont(font);
    highscoreText.setFillColor(sf::Color::White);
    highscoreText.setCharacterSize(30);

    errorText.setFont(font);
    errorText.setFillColor(sf::Color::White);
    errorText.setCharacterSize(24);
    
    menuReturn = new Button("Return to Menu", sf::Vector2f(window->getSize().x/2-100,window->getSize().y-120), sf::Vector2f(200,70), &font, [this]{
        returnToMenu();
    });
}

HighScoreScene::HighScoreScene(sf::RenderWindow* window) : Scene(window) {
    font.loadFromFile("Font/Pixellari.ttf");
    menuReturn = new Button( "", sf::Vector2f(0,0), sf::Vector2f(0,0), &font,[]{});
}

HighScoreScene::~HighScoreScene() {
    delete menuReturn;
}

void HighScoreScene::handleEvent(sf::Event event) {
    if (event.type == sf::Event::Resized) {
        window->setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
        menuReturn->setPosition(sf::Vector2f(window->getSize().x/2-100, window->getSize().y-120));
    }
    if (getName) {
        if (event.type == sf::Event::TextEntered) {
            if (name.size() > 12) {
                errorText.setString("Name must be less than 12 characters.");
                instructionalDelay.restart();
                return;
            }
            // Disallow spaces
            if (event.text.unicode == 32) {
                errorText.setString("Name may not contain spaces.");
                instructionalDelay.restart();
                return;
            }
            // If printable, add character to name
            if (std::isprint(event.text.unicode)) {
                name += event.text.unicode;
            }
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::BackSpace) {
                if (!name.empty()) {
                    name.pop_back();
                }
            }
            if (event.key.code == sf::Keyboard::Return) {
                if (name.size() == 0) {
                    errorText.setString("Cannot accept empty name.");
                    instructionalDelay.restart();
                    return;
                }
                
                setHighScore();
                getName = false;
                return; // avoid string reset
            }
        }
        highscoreText.setString(name);
    } else {
        errorText.setString("");
    }
}

std::pair<int, std::string> HighScoreScene::loadHighScore() {
    std::string word;
    std::ifstream file("data/score");
    if (file.is_open()) {
        std::pair<int, std::string> highscoreData;
        file >> word;
        if (file.eof()) { // If the file only contains a number
            return std::pair<int, std::string>{0,""};
        }
        if (std::all_of(word.begin(),word.end(), ::isdigit)) {
            highscoreData.first = std::stoi(word);
        }
        file >> word;
        highscoreData.second = word;
        return highscoreData;
    }
    // If any errors occur, or if there is no highscore file
    return std::pair<int, std::string>{0,""};
}


void HighScoreScene::setHighScore() {
    std::ofstream file("data/score"); // create and open score file
    file << hs << " " << name;
    highscoreText.setString("Highscore: " +  formatToMinutes(hs) + " by " + name);
}

void HighScoreScene::returnToMenu() {
    transitionScene = new MenuScene(window);
}

// Format time as MM:SS
std::string HighScoreScene::formatToMinutes(int seconds) {
    std::stringstream m;
    std::stringstream s;
    m << std::setfill('0') << std::setw(2) << seconds/60;
    s << std::setfill('0') << std::setw(2) << seconds%60;
    return m.str() + ":" + s.str();
}

bool HighScoreScene::buttonContainsMouse(Button& button) {
    return button.contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window), window->getView()));
}

void HighScoreScene::update(float dt) {
    if (getName) {
        if (name.empty()) {
            highscoreText.setString("Enter your name");
        } else {
            highscoreText.setString(name);
        }
        if (instructionalDelay.getElapsedTime().asSeconds() > 2) {
            errorText.setString("Press enter to confirm your selection");
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonContainsMouse(*menuReturn)) {
        menuReturn->press();
    }
}

void HighScoreScene::draw() {
    if (edit) { // Ensure texts remain centered. Probably more expensive than it needs to be, but its a menu so whatever
    gameEndText.setOrigin(gameEndText.getLocalBounds().width/2, gameEndText.getLocalBounds().height/2);
    gameEndText.setPosition(window->getSize().x/2, window->getSize().y/2-17);

    highscoreText.setOrigin(highscoreText.getLocalBounds().width/2, highscoreText.getLocalBounds().height/2);
    highscoreText.setPosition(window->getSize().x/2, window->getSize().y/2+17);

    errorText.setOrigin(errorText.getLocalBounds().width/2, errorText.getLocalBounds().height/2);
    errorText.setPosition(window->getSize().x/2, window->getSize().y/2+47);
    } else {
        highscoreText.setOrigin(highscoreText.getLocalBounds().width/2, highscoreText.getLocalBounds().height/2);
        highscoreText.setPosition(window->getSize().x/2,window->getSize().y/2);
    }

    window->draw(gameEndText);
    window->draw(highscoreText);
    window->draw(errorText);
    menuReturn->draw(*window);
}