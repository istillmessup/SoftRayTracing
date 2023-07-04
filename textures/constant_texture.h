//
// Created by istil on 2023/6/27.
//

#ifndef SOFTRAYTRACING_CONSTANT_TEXTURE_H
#define SOFTRAYTRACING_CONSTANT_TEXTURE_H

#include "texture.h"

class constant_texture : public texture {
public:
    constant_texture() = default;
    explicit constant_texture(vec3 c) : color(std::move(c)) {}

    vec3 value(double u, double v, const vec3& p) const override { return color; }
public:
    vec3 color;
};


#endif //SOFTRAYTRACING_CONSTANT_TEXTURE_H
