#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Level.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML");
    /*
    sf::Texture texture;
    if (!texture.loadFromFile("baller.png")) {
        std::cerr << "Error! baller.png did not load" << '\n';
        return -1;
    }
    */
    
    std::vector<sf::Texture> textures;
    for (int i = 0; i < 3; ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile(std::to_string(i) + ".png")) {
            return -1;
        }
        textures.push_back(texture);
    }

    Level level("level1.txt", textures, 32);
    
    sf::Clock deltaClock;
    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear();
        level.display(window);
        window.display();
    }
    return 0;
}