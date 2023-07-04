//
// Created by istil on 2023/6/28.
//

#ifndef SOFTRAYTRACING_DIFFUSE_LIGHT_H
#define SOFTRAYTRACING_DIFFUSE_LIGHT_H

#include <utility>

#include "material.h"

class diffuse_light : public material {
public:
    explicit diffuse_light(shared_ptr<texture> a) : emit(std::move(a)) {}

    bool scatter(const ray& ray_in,
                 const hit_record& rec,
                 scatter_record& srec)
                 const override {
        return false;
    }
    vec3 emitted(const ray& ray_in, const hit_record& rec, double u, double v, const vec3& p) const override {
        if (rec.front_face) {
            return {0, 0, 0};
        }
        else {
            return emit->value(u, v, p);
        }
    }
public:
    shared_ptr<texture> emit;
};


#endif //SOFTRAYTRACING_DIFFUSE_LIGHT_H
