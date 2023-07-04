//
// Created by istil on 2023/6/29.
//

#ifndef SOFTRAYTRACING_RECTANGLE_H
#define SOFTRAYTRACING_RECTANGLE_H

#include "hittable_list.h"

enum AXIS {
    X = 1,
    Y,
    Z
};

class rectangle : public hittable {
public:
    rectangle() = default;
    rectangle(int a, double _x0, double _x1, double _y0, double _y1, double _z, shared_ptr<material> mat)
        : axis(a), x0(_x0), x1(_x1), y0(_y0), y1(_y1), z(_z), material(std::move(mat)) {};

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    bool bounding_box(aabb& output_box) const override;

    double pdf_value(const point3& origin, const vec3& v) const override;
    vec3 random(const point3& origin) const override;
public:
    shared_ptr<material> material;
    int axis{};
    double x0{}, x1{}, y0{}, y1{};
    double z{};
};


#endif //SOFTRAYTRACING_RECTANGLE_H
