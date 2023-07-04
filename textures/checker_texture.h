//
// Created by istil on 2023/6/27.
//

#ifndef SOFTRAYTRACING_CHECKER_TEXTURE_H
#define SOFTRAYTRACING_CHECKER_TEXTURE_H

#include "texture.h"

class checker_texture : public texture {
public:
    checker_texture() = default;
    checker_texture(shared_ptr<texture> t0, shared_ptr<texture> t1)
        : even(std::move(t0)), odd(std::move(t1)) {};

    vec3 value(double u, double v, const vec3& p) const override {
        auto sine = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
        if (sine < 0)
            return odd->value(u, v, p);
        else
            return even->value(u, v, p);
    }
public:
    shared_ptr<texture> even;
    shared_ptr<texture> odd;
};


#endif //SOFTRAYTRACING_CHECKER_TEXTURE_H
