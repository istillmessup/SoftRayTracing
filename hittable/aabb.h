//
// Created by istil on 2023/6/27.
//

#ifndef SOFTRAYTRACING_AABB_H
#define SOFTRAYTRACING_AABB_H

#include <utility>

#include "../common.h"

class aabb {
public:
    aabb() = default;
    aabb(vec3 a, vec3 b) : _min(std::move(a)), _max(std::move(b)) {}

    vec3 min() const { return _min; }
    vec3 max() const { return _max; }

    bool hit(const ray& r, double t_min, double t_max) const {
        // 求光线在轴对齐包围盒中时间区间的交集
        for (int i = 0; i < 3; ++i) {
            auto invD = 1.0 / r.direction()[i];
            auto t0 = (_min[i] - r.origin()[i]) * invD;
            auto t1 = (_max[i] - r.origin()[i]) * invD;
            if (invD < 0.0) {
                std::swap(t0, t1);
            }
            t_min = dmax(t0, t_min);
            t_max = dmin(t1, t_max);
            if (t_max <= t_min)
                return false;
        }
        return true;
    }
public:
    vec3 _min;
    vec3 _max;
};


#endif //SOFTRAYTRACING_AABB_H
