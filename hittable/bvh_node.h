//
// Created by istil on 2023/6/27.
//

#ifndef SOFTRAYTRACING_BVH_NODE_H
#define SOFTRAYTRACING_BVH_NODE_H

#include "hittable_list.h"

class bvh_node : public hittable {
public:
    bvh_node() = default;

    explicit bvh_node(hittable_list& list) : bvh_node(list.objects, 0, list.objects.size()) {}

    bvh_node(vector<shared_ptr<hittable>>& objects, size_t start, size_t end);

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
    bool bounding_box(aabb& output_box) const override;
public:
    // hittable指针可以指向sphere、bvh_node或其他任何继承了hittable的类
    shared_ptr<hittable> left;
    shared_ptr<hittable> right;
    aabb box;
};


#endif //SOFTRAYTRACING_BVH_NODE_H
