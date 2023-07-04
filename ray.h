//
// Created by istil on 2023/6/24.
//

#ifndef SOFTRAYTRACING_RAY_H
#define SOFTRAYTRACING_RAY_H

#include <utility>

#include "vec3.h"

// p(t) = a + tb
class ray {
public:
    ray() = default;
    ray(vec3 origin, vec3 direction) : orig(std::move(origin)), dir(std::move(direction)) {}

    vec3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    vec3 at(double t) const { return orig + t * dir;}

private:
    vec3 orig;
    vec3 dir;
};


#endif //SOFTRAYTRACING_RAY_H
