//
// Created by istil on 2023/6/25.
//

#ifndef SOFTRAYTRACING_COMMON_H
#define SOFTRAYTRACING_COMMON_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>

using std::shared_ptr;
using std::make_shared;

const double DOUBLE_INFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180;
}

inline double dmin(double a, double b) { return a <= b ? a : b; }
inline double dmax(double a, double b) { return a >= b ? a : b; }

inline double random_double() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#include "ray.h"
#include "vec3.h"

#endif //SOFTRAYTRACING_COMMON_H
