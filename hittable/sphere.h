//
// Created by istil on 2023/6/24.
//

#ifndef SOFTRAYTRACING_SPHERE_H
#define SOFTRAYTRACING_SPHERE_H

#include <utility>

#include "hittable_list.h"

class sphere : public hittable{
public:
    sphere() = default;
    sphere(vec3 cen, double r, shared_ptr<material> m)
        : center(std::move(cen)), radius(r), material_ptr(std::move(m)) {};

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    bool bounding_box(aabb& output_box) const override;
    double pdf_value(const point3& o, const vec3& v) const override;
    vec3 random(const point3& o) const override;


    void get_sphere_uv(const vec3& p, double& u, double& v) const;
public:
    vec3 center;
    double radius = 0.0;
    shared_ptr<material> material_ptr;
};


#endif //SOFTRAYTRACING_SPHERE_H
