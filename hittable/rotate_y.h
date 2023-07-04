//
// Created by istil on 2023/6/30.
//

#ifndef SOFTRAYTRACING_ROTATE_Y_H
#define SOFTRAYTRACING_ROTATE_Y_H

#include "hittable_list.h"

class rotate_y : public hittable {
public:
    rotate_y(shared_ptr<hittable> p, double angle);

    bool hit(const ray&r, double t_min, double t_max, hit_record& rec) const override;
    bool bounding_box(aabb& output_box) const override {
        output_box = b_box;
        return has_box;
    }
public:
    shared_ptr<hittable> ptr;
    double sin_theta;
    double cos_theta;
    bool has_box;
    aabb b_box;
};


#endif //SOFTRAYTRACING_ROTATE_Y_H
