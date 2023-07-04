//
// Created by istil on 2023/6/28.
//

#ifndef SOFTRAYTRACING_NOISE_TEXTURE_H
#define SOFTRAYTRACING_NOISE_TEXTURE_H

#include "perlin.h"

class noise_texture : public texture{
public:
    noise_texture() = default;
    explicit noise_texture(double sc) : scale(sc) {}

    vec3 value(double u, double v, const vec3& p) const override {
        auto n = noise.turb(p);
        return vec3(1, 1, 1) * 0.5 * (1.0 + sin(scale * p.z() + 10 * n));
    }
public:
    perlin noise;
    double scale = 1.0;
};


#endif //SOFTRAYTRACING_NOISE_TEXTURE_H
