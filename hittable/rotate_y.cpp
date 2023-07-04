//
// Created by istil on 2023/6/30.
//

#include "rotate_y.h"

rotate_y::rotate_y(shared_ptr<hittable> p, double angle) : ptr(std::move(p)) {
    auto radians = degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    has_box = ptr->bounding_box(b_box);

    vec3 min( DOUBLE_INFINITY,  DOUBLE_INFINITY,  DOUBLE_INFINITY);
    vec3 max(-DOUBLE_INFINITY, -DOUBLE_INFINITY, -DOUBLE_INFINITY);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                auto x = i * b_box.max().x() + (1 - i) * b_box.max().x();
                auto y = j * b_box.max().y() + (1 - j) * b_box.max().y();
                auto z = k * b_box.max().z() + (1 - k) * b_box.max().z();

                auto new_x =  cos_theta * x + sin_theta * z;
                auto new_z = -sin_theta * x + cos_theta * z;
                vec3 tester(new_x, y, new_z);

                for (int c = 0; c < 3; ++c) {
                    min[c] = dmin(min[c], tester[c]);
                    max[c] = dmax(max[c], tester[c]);
                }
            }
        }
    }
    b_box = aabb(min, max);
}

bool rotate_y::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    vec3 origin = r.origin();
    vec3 direction = r.direction();

    // 逆旋转
    origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
    origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];

    direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
    direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

    ray rotated_r(origin, direction);

    if (!ptr->hit(rotated_r, t_min, t_max, rec)) {
        return false;
    }

    vec3 p = rec.p;
    vec3 normal = rec.normal;

    p[0] =  cos_theta * rec.p[0] + sin_theta * rec.p[2];
    p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

    normal[0] =  cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

    rec.p = p;
    rec.set_face_normal(rotated_r, normal);

    return true;
}
