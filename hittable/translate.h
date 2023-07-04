//
// Created by istil on 2023/6/30.
//

#ifndef SOFTRAYTRACING_TRANSLATE_H
#define SOFTRAYTRACING_TRANSLATE_H

#include <utility>

#include "hittable_list.h"

class translate : public hittable {
public:
    translate(shared_ptr<hittable> p, vec3 displacement) : ptr(std::move(p)), offset(std::move(displacement)) {}

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    bool bounding_box(aabb& output_box) const override;
public:
    shared_ptr<hittable> ptr;
    vec3 offset;
};


#endif //SOFTRAYTRACING_TRANSLATE_H
