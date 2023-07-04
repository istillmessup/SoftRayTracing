//
// Created by istil on 2023/6/25.
//

#include "hittable_list.h"

bool hittable_list::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    hit_record record;
    bool is_hit = false;
    auto z_buffer = t_max;

    // 遍历场景中的每个物体，寻找最近的交点
    for (const auto& object : objects) {
        if (object->hit(r, t_min, z_buffer, record)) {
            is_hit = true;
            z_buffer = record.t;
            rec = record;
        }
    }
    return is_hit;
}



bool hittable_list::bounding_box(aabb &output_box) const {
    if (objects.empty()) return false;

    // 计算场景所所有物体的总包围盒
    aabb temp_box;
    bool first_box = true;
    for (const auto& object : objects) {
        if (!object->bounding_box(temp_box)) {
            return false;
        }
        output_box = first_box ? temp_box : surrounding_box(temp_box, output_box);
        first_box = false;
    }
    return true;
}

double hittable_list::pdf_value(const point3 &o, const vec3 &v) const {
    auto weight = 1.0 / objects.size();
    auto sum = 0.0;

    for (const auto& object : objects) {
        sum += weight * object->pdf_value(o, v);
    }
    return sum;
}

vec3 hittable_list::random(const vec3 &o) const {
    auto int_size = static_cast<int>(objects.size());
    return objects[static_cast<int>(random_double(0, int_size))]->random(o);
}
