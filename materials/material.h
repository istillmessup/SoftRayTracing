//
// Created by istil on 2023/6/26.
//

#ifndef SOFTRAYTRACING_MATERIAL_H
#define SOFTRAYTRACING_MATERIAL_H

#include "../common.h"
#include "../hittable/hittable.h"
#include "../textures/constant_texture.h"
#include "../textures/checker_texture.h"
#include "../textures/noise_texture.h"
#include "../textures/image_texture.h"
#include "../onb.h"
#include "../pdf/cosine_pdf.h"

inline double schlick(double cosine, double eta) {
    auto r0 = (1 - eta) / (1 + eta);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

// 散射光线的信息
struct scatter_record {
    ray specular_ray;
    bool is_specular;
    color albedo;
    shared_ptr<pdf> pdf_ptr;
};

class material {
public:
    virtual bool scatter(const ray& ray_in, const hit_record& rec, scatter_record& srec) const {
        return false;
    }

    virtual double scattering_pdf(const ray& ray_in, const hit_record& rec, const ray& scattered) const {
        return 0;
    }

    virtual color emitted(const ray& ray_in, const hit_record& rec, double u, double v, const vec3& p) const {
        return {0, 0, 0};
    }
};


#endif //SOFTRAYTRACING_MATERIAL_H
