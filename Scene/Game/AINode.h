#ifndef AINODE_H
#define AINODE_H

#include <limits>

/*
* AINode utility class to be used by AI Input
*/

class AINode {
public:
    AINode(int x, int y, bool traversable) : x(x), y(y), traversable(traversable) {}
    void resetAIParams() {
        gCost = fCost = std::numeric_limits<int>::infinity();
        hCost = 0;
        parent = nullptr;
    }
    int x;
    int y;
    bool traversable;
    int gCost = std::numeric_limits<int>::infinity();
    int hCost = 0;
    int fCost = std::numeric_limits<int>::infinity();
    AINode* parent = nullptr;
};

#endif