#include "Tester.h"

#include "Level.h"
#include "Entity.h"
#include "Commando.h"
#include "InputHandler.h"
#include "AIInput.h"
#include "MathUtil.h"
#include "HighscoreScene.h"

#include <cassert>
#include <filesystem>

void Tester::testPathFinding() {
    Level level("Testing/test_level.txt", "img/level1.png",32,{2},{});
    AIInput ai(nullptr, &level);
    AINode selfNode = AINode(1,1, true);
    AINode targetNode = AINode(4,3, true);
    std::stack<AINode*> path = ai.findPath(selfNode, targetNode);
    std::deque<std::pair<int,int>> correctPath = {std::pair(1, 1), std::pair(2,1), std::pair(3,1), std::pair(4,1),std::pair(5,1),std::pair(5,2),
                                                   std::pair(5,3),std::pair(4,3)};
    while (!path.empty()) {
        assert((!path.empty() == !correctPath.empty()) && "Pathfinding Case 1: Path size does not match");
        assert(((path.top()->x == correctPath[0].first) && (path.top()->y == correctPath[0].second)) && "Pathfinding Case 1: Path does not match correct path");
        path.pop();
        correctPath.pop_front();
    }
    std::cout << "Pathfinding Case 1 Success!\n";
    path = ai.findPath(selfNode,selfNode);
    assert(!path.empty() && "Pathfinding Case 2: Path not reported");
    assert((path.top()->x == selfNode.x && path.top()->y == selfNode.y) && "Pathfinding Case 2: Path not reported correctly");
    std::cout << "Pathfinding Case 2 Success!\n";
}

void Tester::testEntityCollision() {
    Level level("Testing/test_level.txt", "img/level1.png",32,{2},{});
    Commando testPlayer(nullptr, sf::Vector2f(0,0), Team::ALLY, nullptr);
    assert(testPlayer.isColliding(level)  && "Collision Case 1: Player is not reported as colliding");
    std::cout << "Collision Case 1 Success!\n";
    testPlayer.sprite.setPosition(32, 32);
    assert(!testPlayer.isColliding(level) && "Collision Case 2: Player is reported as colliding");
    std::cout << "Collision Case 2 Success!\n";
}

void Tester::testMathUtil() {
    assert((MathUtil<sf::Vector2f>::normalize(sf::Vector2f(0,0)) == sf::Vector2f(0,0)) && "Normalize Case 1: Zero vector became nonzero");
    std::cout << "Normalize Case 1 Success!\n";
    assert((MathUtil<sf::Vector2f>::length(MathUtil<sf::Vector2f>::normalize(sf::Vector2f(1,1)))) && "Normalize Case 2: Vectors length != 1");
    std::cout << "Normalize Case 2 Success!\n";
    assert((std::abs((MathUtil<sf::Vector2f>::distance(sf::Vector2f(0,0), sf::Vector2f(1,1)) - std::sqrt(2))) < 0.001) && "Distance Case 1: Distance not reported correctly");
    std::cout << "Distance Case 1 Success!\n";
    assert((MathUtil<sf::Vector2f>::distance(sf::Vector2f(1,1), sf::Vector2f(1,1)) == 0) && "Distance Case 2: Distance not reported correctly");
    std::cout << "Distance Case 2 Success!\n";
    assert((MathUtil<sf::Vector2f>::length(sf::Vector2f(0,1))==1) && "Length Case 1: Length != 1");
    std::cout << "Length Case 1 Success!\n";
    assert((MathUtil<sf::Vector2f>::length(sf::Vector2f(0,0)) == 0) && "Length Case 2: Length != 0");
    std::cout << "Length Case 2 Success!\n";
    assert((std::abs(MathUtil<sf::Vector2f>::length(sf::Vector2f(1,1)) - std::sqrt(2)) < 0.001) && "Length Case 3: Length != approx Sqrt(2)");
    std::cout << "Length Case 3 Success!\n";
}

void Tester::testLoadHighscore() {
    // Rename user score file to preserve score
    std::filesystem::path p = std::filesystem::current_path();
    if (std::filesystem::exists("data/score")) {
        std::filesystem::rename(p/"data/score", p/"data/tempscore");
    }
    sf::RenderWindow fakeWindow;
    HighScoreScene hsscene(&fakeWindow);
    std::pair<int, std::string> hs = hsscene.loadHighScore();
    assert((hs.first == 0 && hs.second == "") && "Highscore Case 1: Highscore did not return null.");
    std::cout << "Highscore Case 1 Success!\n";
    hsscene.name = "Test";
    hsscene.hs = 100;
    hsscene.setHighScore();
    hs = hsscene.loadHighScore();
    assert((hs.first == 100 && hs.second == "Test") && "Highscore Case 2: Highscore did not load correctly");
    std::cout << "Highscore Case 2 Success!\n";
    // Revert testing changes
    std::filesystem::remove(p/"data/score");
    if (std::filesystem::exists("data/tempscore")) {
        std::filesystem::rename(p/"data/tempscore", p/"data/score");
    }
}

void Tester::runTests() {
    testPathFinding();
    testMathUtil();
    testLoadHighscore();
    testEntityCollision();
}