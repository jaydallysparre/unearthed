#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>
#include <SFML/Graphics.hpp>

template<typename T>
class MathUtil {
private:
    MathUtil(); // private constructor to prevent instantiation
public:
    // Returns normalized vector (length 1)
    static T normalize(T vector) { 
        T normalizedVec;
        float magnitude = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
        if (magnitude == 0) {
            normalizedVec.x = 0;
            normalizedVec.y = 0;
        } else {
            normalizedVec.x = vector.x / magnitude;
            normalizedVec.y = vector.y / magnitude;
        }
        return normalizedVec;
    }
    
    // Get the distance between two vectors
    static float distance(T vector1, T vector2) {
        return std::sqrt(std::pow(vector1.x-vector2.x,2) + std::pow(vector1.y-vector2.y, 2));
    }

    // Get the length of a vector
    static float length(T vector) {
        return std::sqrt(std::pow(vector.x,2) + std::pow(vector.y,2));
    }
};

#endif