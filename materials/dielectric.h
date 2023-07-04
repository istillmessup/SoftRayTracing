//
// Created by istil on 2023/6/26.
//

#ifndef SOFTRAYTRACING_DIELECTRIC_H
#define SOFTRAYTRACING_DIELECTRIC_H

#include "material.h"

class dielectric : public material{
public:
    explicit dielectric(double e) : eta(e) {}
    bool scatter(const ray& ray_in,
                 const hit_record& rec,
                 scatter_record& srec)
                 const override {
        // 完美的绝缘体介质不会吸收任何光
        srec.is_specular = true;
        srec.pdf_ptr = nullptr;
        srec.albedo = color(1, 1, 1);
        double etai_over_etat;
        // 空气和绝缘体之间的折射
        if (rec.front_face) {
            etai_over_etat = 1.0 / eta;
        }
        else {
            etai_over_etat = eta;
        }
        // 根据出射角判断发生折射还是反射
        vec3 normalized_direction = normalize(ray_in.direction());
        double cos_theta = dmin(dot(-normalized_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
        // 全反射
        if (etai_over_etat * sin_theta > 1.0) {
            vec3 reflect_direction = reflect(normalized_direction, rec.normal);
            srec.specular_ray = ray(rec.p, reflect_direction);
            return true;
        }
        // 这里因为采样很多，用了一个trick：一条光线要么全部反射要么全部折射，取均值后效果也一样
        // 发生反射的部分
        double reflect_prob = schlick(cos_theta, etai_over_etat);
        if (random_double() < reflect_prob) {
            vec3 reflect_direction = reflect(normalized_direction, rec.normal);
            srec.specular_ray = ray(rec.p, reflect_direction);
            return true;
        }
        // 发生折射的部分
        vec3 refract_direction = refract(normalized_direction, rec.normal, etai_over_etat);
        srec.specular_ray = ray(rec.p, refract_direction);
        return true;
    }
public:
    // 折射率
    double eta;
};


#endif //SOFTRAYTRACING_DIELECTRIC_H
