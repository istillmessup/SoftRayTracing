//
// Created by istil on 2023/6/30.
//

#include "translate.h"

bool translate::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    // 平移物体等价于反向平移光线
    ray moved_r(r.origin() - offset, r.direction());
    if (!ptr->hit(moved_r, t_min, t_max, rec)) {
        return false;
    }
    // 实际上的交点坐标
    rec.p += offset;
    rec.set_face_normal(moved_r, rec.normal);
    return true;
}

bool translate::bounding_box(aabb &output_box) const {
    if (!ptr->bounding_box(output_box)) {
        return false;
    }
    output_box = aabb(output_box.min() + offset, output_box.max() + offset);
    return true;
}
