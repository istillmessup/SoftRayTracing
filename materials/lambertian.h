//
// Created by istil on 2023/6/26.
//

#ifndef SOFTRAYTRACING_LAMBERTIAN_H
#define SOFTRAYTRACING_LAMBERTIAN_H

#include <utility>

#include "material.h"

class lambertian : public material {
public:
    explicit lambertian(const color& a) : albedo(make_shared<constant_texture>(a)) {}
    explicit lambertian(shared_ptr<texture> a) : albedo(std::move(a)) {}

    // 定义漫反射方向
    bool scatter(const ray& ray_in,
                 const hit_record& rec,
                 scatter_record& srec)
                 const override {
        // 以法向为中心的半球上随机采样
        srec.is_specular = false;
        srec.albedo = albedo->value(rec.u, rec.v, rec.p);
        srec.pdf_ptr = make_shared<cosine_pdf>(cosine_pdf(rec.normal));
        return true;
    }

    double scattering_pdf(const ray& ray_in, const hit_record& rec, const ray& scattered) const override {
        auto cosine = dot(rec.normal, normalize(scattered.direction()));
        return cosine < 0 ? 0 : cosine / PI;
    }

public:
    // 光强度衰减率
    shared_ptr<texture> albedo;
};


#endif //SOFTRAYTRACING_LAMBERTIAN_H
