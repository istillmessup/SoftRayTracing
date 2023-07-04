//
// Created by istil on 2023/7/2.
//

#ifndef SOFTRAYTRACING_ONB_H
#define SOFTRAYTRACING_ONB_H

#include "common.h"

// 标准正交基，以表面法向n作为z轴正方向
class onb {
public:
    onb() = default;
    inline vec3 operator[](int i) const { return axis[i]; }

    vec3 u() const { return axis[0]; }
    vec3 v() const { return axis[1]; }
    vec3 w() const { return axis[2]; }

    vec3 local(double x, double y, double z) const {
        return x * u() + y * v() + z * w();
    }

    vec3 local(const vec3& vec) const {
        return vec.x() * u() + vec.y() * v() + vec.z() * w();
    }

    void build_from_w(const vec3& vec);
public:
    vec3 axis[3];
};


#endif //SOFTRAYTRACING_ONB_H
