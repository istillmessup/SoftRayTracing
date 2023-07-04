//
// Created by istil on 2023/6/24.
//

#include "sphere.h"

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // (p(t) - c) · (p(t) - c) = R^2
    // p(t) = a + tb
    // t^2 * b · b + t * 2b(a - c) + (a - c) · (a - c) - R^2
    vec3 a_minus_c = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(r.direction(), a_minus_c);
    auto c = dot(a_minus_c, a_minus_c) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        // 求球面交点和表面法向
        auto t = (-b - root) / (2.0 * a);
        if (t > t_min && t < t_max) {
            // 交点坐标
            rec.p = r.at(t);
            // z_buffer
            rec.t = t;
            // 法向
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            // 纹理
            rec.material_ptr = material_ptr;
            // 纹理坐标
            get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
            return true;
        }
        t = (-b + root) / (2.0 * a);
        if (t > t_min && t < t_max) {
            rec.p = r.at(t);
            rec.t = t;
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.material_ptr = material_ptr;
            get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
            return true;
        }
    }
    return false;
}

bool sphere::bounding_box(aabb &output_box) const {
    output_box = aabb(
            center - vec3(radius, radius, radius),
            center + vec3(radius, radius, radius)
            );
    return true;
}

void sphere::get_sphere_uv(const vec3 &p, double &u, double &v) const { /* NOLINT */
    auto phi = atan2(p.z(), p.x());
    auto theta = asin(p.y());

    u = 1 - (phi + PI) / (2 * PI);
    v = (theta + PI / 2) / PI;
}

double sphere::pdf_value(const point3 &o, const vec3 &v) const {
    hit_record rec;
    if (!this->hit(ray(o, v), 0.000001, DOUBLE_INFINITY, rec)) {
        return 0;
    }

    auto cos_theta_max = sqrt(1 - radius * radius / (center - o).length_squared());
    auto solid_angle = 2 * PI * (1 - cos_theta_max);

    return 1 / solid_angle;
}

vec3 sphere::random(const point3 &o) const {
    vec3 direction = center - o;
    auto distance_squared = direction.length_squared();
    onb uvw;
    uvw.build_from_w(direction);
    return uvw.local(vec3::random_to_sphere(radius, distance_squared));
}

