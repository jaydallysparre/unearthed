#ifndef TESTER_H
#define TESTER_H

#include <SFML/Graphics.hpp>

class Tester {
private:
    static void testPathFinding();
    static void testEntityCollision();
    static void testMathUtil();
    static void testLoadHighscore();
    static void testSceneSwitch();
public:
    static void runTests();
};

#endif