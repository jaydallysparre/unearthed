#include "HighscoreScene.h"
#include <fstream>
#include <string>
#include <iostream>

HighScoreScene::HighScoreScene(sf::RenderWindow* window, bool edit, int score) : Scene(window), edit(edit), hs(score) {
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
    }
    if (highscore > 0 || !getName) {
        highscoreText.setString("Highscore: " + std::to_string(highscore) + " by " + highscoreData.second);
    }
    gameEndText.setFont(font);
    gameEndText.setFillColor(sf::Color::White);
    gameEndText.setCharacterSize(30);
    highscoreText.setFont(font);
    highscoreText.setFillColor(sf::Color::White);
    highscoreText.setCharacterSize(30);
}

void HighScoreScene::handleEvent(sf::Event event) {
    if (event.type == sf::Event::Resized) {
        window->setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
    }
    if (getName) {
        if (event.type == sf::Event::TextEntered) {
            if (std::isprint(event.text.unicode)) {
                name += event.text.unicode;
            }
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::BackSpace) {
                if (!name.empty()) {
                    name.pop_back();
                }
            }
            if (event.key.code == sf::Keyboard::Return || name.size() > 12) {
                setHighScore();
                getName = false;
                return; // avoid string reset
            }
        }
        typeDelay.restart();
        highscoreText.setString(name);
    }
}

std::pair<int, std::string> HighScoreScene::loadHighScore() {
    std::string word;
    std::ifstream file("score");
    if (file.is_open()) {
        std::pair<int, std::string> highscoreData;
        file >> word;
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
    std::ofstream file("score"); // create and open score file
    file << hs << name;
    highscoreText.setString("Highscore: " + std::to_string(hs) + " by " + name);
}

void HighScoreScene::update(float dt) {
    if (getName) {
        if (name.empty()) {
            highscoreText.setString("Enter your name");
        } else {
            highscoreText.setString(name);
        }
    }
}

void HighScoreScene::draw() {
    gameEndText.setOrigin(gameEndText.getLocalBounds().width/2, gameEndText.getLocalBounds().height/2);
    gameEndText.setPosition(window->getSize().x/2, window->getSize().y/2-15);
    window->draw(gameEndText);

    highscoreText.setOrigin(highscoreText.getLocalBounds().width/2, highscoreText.getLocalBounds().height/2);
    highscoreText.setPosition(window->getSize().x/2, window->getSize().y/2+15);
    window->draw(highscoreText);
}