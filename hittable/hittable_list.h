//
// Created by istil on 2023/6/25.
//

#ifndef SOFTRAYTRACING_HITTABLE_LIST_H
#define SOFTRAYTRACING_HITTABLE_LIST_H

#include "hittable.h"
#include "../onb.h"

using std::shared_ptr;
using std::vector;

class hittable_list : public hittable {
public:
    hittable_list() = default;
    explicit hittable_list(const shared_ptr<hittable>& object) { add(object); }

    void clear() { objects.clear(); }
    void add(const shared_ptr<hittable>& object) { objects.push_back(object); }

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    bool bounding_box(aabb& output_box) const override;
    double pdf_value(const point3& o, const vec3& v) const override;
    vec3 random(const vec3& o) const override;
public:
    // 使用智能指针的目的是为了能让多个几何图元共享一个实例，例如多个物体共享同一个材质
    vector<shared_ptr<hittable>> objects;
};

inline aabb surrounding_box(const aabb& box0, const aabb& box1) {
    vec3 small(dmin(box0.min().x(), box1.min().x()),
               dmin(box0.min().y(), box1.min().y()),
               dmin(box0.min().z(), box1.min().z()));
    vec3 big  (dmax(box0.max().x(), box1.max().x()),
               dmax(box0.max().y(), box1.max().y()),
               dmax(box0.max().z(), box1.max().z()));
    return {small,big};
}

#endif //SOFTRAYTRACING_HITTABLE_LIST_H
