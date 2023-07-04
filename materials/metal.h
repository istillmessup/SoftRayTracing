//
// Created by istil on 2023/6/26.
//

#ifndef SOFTRAYTRACING_METAL_H
#define SOFTRAYTRACING_METAL_H

#include <utility>

#include "material.h"

class metal : public material {
public:
    metal(vec3 a, double f) : albedo(std::move(a)), fuzz(f) {}

    bool scatter(const ray& ray_in,
                 const hit_record& rec,
                 scatter_record& srec)
                 const override {
        vec3 reflect_direction = reflect(normalize(ray_in.direction()), rec.normal);
        srec.specular_ray = ray(rec.p, reflect_direction + fuzz * vec3::random_normalized_vector());
        srec.albedo = albedo;
        srec.is_specular = true;
        srec.pdf_ptr = nullptr;
        return true;
    }

public:
    vec3 albedo;
    double fuzz;
};


#endif //SOFTRAYTRACING_METAL_H
