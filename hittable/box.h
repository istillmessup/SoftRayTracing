//
// Created by istil on 2023/6/30.
//

#ifndef SOFTRAYTRACING_BOX_H
#define SOFTRAYTRACING_BOX_H

#include "rectangle.h"

class box : public hittable {
public:
    box() = default;
    box(const vec3& p0, const vec3& p1, const shared_ptr<material>& ptr);

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        return sides.hit(r, t_min, t_max, rec);
    }
    bool bounding_box(aabb& output_box) const override {
        output_box = aabb(box_min, box_max);
        return true;
    }
public:
    // 盒子在初始化的时候是轴对齐的，分别表示左下角和右上角的点
    vec3 box_min;
    vec3 box_max;
    hittable_list sides;
};


#endif //SOFTRAYTRACING_BOX_H
