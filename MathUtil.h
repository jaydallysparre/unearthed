#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>
#include <SFML/Graphics.hpp>

template<typename T>
class MathUtil {
private:
    MathUtil(); // private constructor to prevent instantiation
public:
    static T normalize(T vector) { // defined in header file due to template
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
};

#endif