#ifndef TESTER_H
#define TESTER_H

#include <SFML/Graphics.hpp>

/*
* Class for Unit Testing functions
*/

class Tester {
private:
    // Test pathfinding algorithm
    static void testPathFinding();

    // Test entity collision
    static void testEntityCollision();

    // Test the math utility functions
    static void testMathUtil();

    // Test highscore loading
    static void testLoadHighscore();
public:
    // Run all tests
    static void runTests();
};

#endif