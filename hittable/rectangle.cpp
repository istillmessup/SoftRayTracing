//
// Created by istil on 2023/6/29.
//

#include "rectangle.h"

bool rectangle::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
    double t, x, y;
    vec3 outward_normal;
    // TODO：这里还是比较冗余，后续看看怎么优化
    switch (axis) {
        case X:
            t = (z - r.origin().x()) / r.direction().x();
            x = r.origin().y() + t * r.direction().y();
            y = r.origin().z() + t * r.direction().z();
            outward_normal = vec3(1, 0, 0);
            break;
        case Y:
            t = (z - r.origin().y()) / r.direction().y();
            x = r.origin().x() + t * r.direction().x();
            y = r.origin().z() + t * r.direction().z();
            outward_normal = vec3(0, 1, 0);
            break;
        case Z:
            t = (z - r.origin().z()) / r.direction().z();
            x = r.origin().x() + t * r.direction().x();
            y = r.origin().y() + t * r.direction().y();
            outward_normal = vec3(0, 0, 1);
            break;
        default:
            return false;
    }

    if (t < t_min || t > t_max) {
        return false;
    }

    if (x < x0 || x > x1 || y < y0 || y > y1) {
        return false;
    }

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;

    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = material;
    rec.p = r.at(t);

    return true;
}

bool rectangle::bounding_box(aabb &output_box) const {
    switch (axis) {
        case X:
            output_box = aabb(vec3(z - 0.0001, x0, y0), vec3(z + 0.0001, x1, y1));
            break;
        case Y:
            output_box = aabb(vec3(x0, z - 0.0001, y0), vec3(x1, z + 0.0001, y1));
            break;
        case Z:
            output_box = aabb(vec3(x0, y0, z - 0.0001), vec3(x1, y1, z + 0.0001));
            break;
        default:
            return false;
    }

    return true;
}

double rectangle::pdf_value(const point3 &origin, const vec3 &v) const {
    hit_record rec;
    if (!this->hit(ray(origin, v), 0.001, DOUBLE_INFINITY, rec)) {
        return 0;
    }

    auto area = (x1 - x0) * (y1 - y0);
    auto distance_squared = rec.t * rec.t * v.length_squared();
    auto cosine = fabs(dot(v, rec.normal) / v.length());

    return distance_squared / (cosine * area);
}

vec3 rectangle::random(const point3 &origin) const {
    // 连接光源和反射点的向量
    auto random_point = point3(random_double(x0, x1), z, random_double(y0, y1));
    return random_point - origin;
}
