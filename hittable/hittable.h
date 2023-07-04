//
// Created by istil on 2023/6/24.
//

#ifndef SOFTRAYTRACING_HITTABLE_H
#define SOFTRAYTRACING_HITTABLE_H

#include "../common.h"
#include "aabb.h"

class material;

struct hit_record {
    vec3 p;
    vec3 normal;
    shared_ptr<material> material_ptr;
    double t = 0.0;
    double u = 0.0;
    double v = 0.0;
    bool front_face = true;

    // 实现双面材质，通常表面法向向外，当光线从内部打到物体表面时要反转法向
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    // 相交有效范围[t_min, tmax]
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
    virtual bool bounding_box(aabb& output_box) const = 0;
    // 采样概率分布函数
    virtual double pdf_value(const point3& o, const vec3& v) const { return 0.0; }
    // 采样方向
    virtual vec3 random(const vec3& o) const { return {1, 0, 0}; }
};


#endif //SOFTRAYTRACING_HITTABLE_H
