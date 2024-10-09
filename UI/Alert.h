#ifndef ALERT_H
#define ALERT_H

#include <string>
#include <SFML/Graphics.hpp>

class Alert {
private:
    std::string text;
    int alertTime;
    int priority;
public:
    Alert(std::string text, int alertTime, int priority=0) : text(text), alertTime(alertTime), priority(priority) {}
    std::string getText() const {
        return text;
    }
    int getTime() const {
        return alertTime;
    }
    int getPriority() const {
        return priority;
    }
    bool operator>(const Alert& other) const { // For priority queue
        return this->priority > other.getPriority();
    }
};

#endif