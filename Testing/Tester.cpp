#include "Tester.h"

#include "Level.h"
#include "Entity.h"
#include "Commando.h"
#include "InputHandler.h"
#include "AIInput.h"
#include "MathUtil.h"

#include <cassert>

void Tester::testPathFinding() {
    Level level("Testing/test_level.txt", "level1.png",32,{2},{});
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
    std::cout << "Pathfinding Case 1 Success!" << '\n';
}

void Tester::testEntityCollision() {

}

void Tester::testMathUtil() {
    assert((MathUtil<sf::Vector2f>::normalize(sf::Vector2f(0,0)) == sf::Vector2f(0,0)) && "Normalize Case 1: Zero vector became nonzero");
    std::cout << "Normalize Case 1 Success!" << '\n';
    assert((MathUtil<sf::Vector2f>::length(MathUtil<sf::Vector2f>::normalize(sf::Vector2f(1,1)))) && "Normalize Case 2: Vectors length != 1");
    std::cout << "Normalize Case 2 Success!" << '\n';
    assert((std::abs((MathUtil<sf::Vector2f>::distance(sf::Vector2f(0,0), sf::Vector2f(1,1)) - std::sqrt(2))) < 0.001) && "Distance Case 1: Distance not reported correctly");
    std::cout << "Distance Case 1 Success!" << '\n';
    assert((MathUtil<sf::Vector2f>::length(sf::Vector2f(0,1))==1) && "Length Case 1: Length != 1");
    std::cout << "Length Case 1 Success!" << '\n';
    assert((MathUtil<sf::Vector2f>::length(sf::Vector2f(0,0)) == 0) && "Length Case 2: Length != 0");
    std::cout << "Length Case 2 Success!" << '\n';
    assert((std::abs(MathUtil<sf::Vector2f>::length(sf::Vector2f(1,1)) - std::sqrt(2)) < 0.001) && "Length Case 3: Length != approx Sqrt(2)");
    std::cout << "Length Case 3 Success!" << '\n';
}

void Tester::testLoadHighscore() {
    
}

void Tester::testSceneSwitch() {

}

void Tester::runTests() {
    testPathFinding();
    testMathUtil();
}