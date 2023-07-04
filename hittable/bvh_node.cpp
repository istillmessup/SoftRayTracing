//
// Created by istil on 2023/6/27.
//

#include "bvh_node.h"
#include <algorithm>

inline bool box_compare(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b, int axis) {
    aabb box_a;
    aabb box_b;
    if (!a->bounding_box(box_a) || !b->bounding_box(box_b)) {
        std::cerr << "No Bounding Box in bvh_node Constructor.\n";
    }
    return box_a.min().vec[axis] < box_b.min().vec[axis];
}

bool box_x_compare(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) {
    return box_compare(a, b, 0);
}

bool box_y_compare(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) {
    return box_compare(a, b, 1);
}

bool box_z_compare(const shared_ptr<hittable>& a, const shared_ptr<hittable>& b) {
    return box_compare(a, b, 2);
}

bvh_node::bvh_node(vector<shared_ptr<hittable>> &objects, size_t start, size_t end) {
    int axis = (int)random_double(0, 3);
    auto comparator = (axis == 0) ? box_x_compare
                    : (axis == 1) ? box_y_compare
                                  : box_z_compare;
    size_t object_span = end - start;

    // 只剩一个物体，同时保存在左右叶子节点上
    if (object_span == 1) {
        left = right = objects[start];
    }
    // 剩两个物体，分别保存在左右叶子节点上
    else if (object_span == 2) {
        if (comparator(objects[start], objects[start + 1])) {
            left = objects[start];
            right = objects[start + 1];
        }
        else {
            left = objects[start + 1];
            right = objects[start];
        }
    }
    // 将包围盒内的物体评分到左右子树上
    else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        left = make_shared<bvh_node>(objects, start, mid);
        right = make_shared<bvh_node>(objects, mid, end);
    }

    aabb box_left, box_right;
    if (!left->bounding_box(box_left) || !right->bounding_box(box_right)) {
        std::cerr << "No Bounding Box in bvh_node Constructor./n";
    }
    box = surrounding_box(box_left, box_right);
}

bool bvh_node::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    // aabb->hit
    if (!box.hit(r, t_min, t_max)) {
        return false;
    }

    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

bool bvh_node::bounding_box(aabb &output_box) const {
    output_box = box;
    return true;
}
