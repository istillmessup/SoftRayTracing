//
// Created by istil on 2023/6/24.
//

#ifndef SOFTRAYTRACING_VEC3_H
#define SOFTRAYTRACING_VEC3_H

#include <vector>
#include <cmath>
#include <iostream>

class vec3 {
public:
    vec3() : vec({0, 0, 0}) {};
    vec3(double x, double y, double z) : vec({x, y, z}) {}

    double x() const { return vec[0]; };
    double y() const { return vec[1]; };
    double z() const { return vec[2]; };

    // 操作符重载
    vec3 operator-() const { return {-vec[0], -vec[1], -vec[2]}; }
    double operator[](int index) const { return vec[index]; }
    double& operator[](int index) { return vec[index]; }

    vec3& operator+=(const vec3& v) {
        vec[0] += v[0];
        vec[1] += v[1];
        vec[2] += v[2];
        return *this;
    }

    vec3& operator*=(const double t) {
        vec[0] *= t;
        vec[1] *= t;
        vec[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t) {
        return *this *= (1 / t);
    }

    double length() const { return sqrt(length_squared()); }

    double length_squared() const { return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];}

    bool near_zero() const {
        const auto s = 1e-8;
        return fabs(vec[0]) < s && fabs(vec[1]) < s && fabs(vec[2]) < s;
    }

    void write_color(std::ostream& out, int samples_per_pixel);

    static vec3 random();
    static vec3 random(double, double);
    // 返回单位球面上随机任意一点
    static vec3 random_normalized_vector();
    static vec3 random_in_normalized_disk();

    static vec3 random_cosine_direction();
    static vec3 random_to_sphere(double radius, double distance_squared);

    std::vector<double> vec;
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return {u[0] + v[0], u[1] + v[1], u[2] + v[2]};
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return u + (-v);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return {u[0] * v[0], u[1] * v[1], u[2] * v[2]};
}

inline vec3 operator*(double t, const vec3& v) {
    return {t * v[0], t * v[1], t * v[2]};
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return {u[1] * v[2] - u[2] * v[1],
            u[2] * v[0] - u[0] * v[2],
            u[0] * v[1] - u[1] * v[0]};
}

inline vec3 normalize(const vec3& v) {
    return v / v.length();
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

inline vec3 refract (const vec3& v, const vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-v, n);
    // 水平方向分量
    vec3 r_out_parallel = etai_over_etat * (v + cos_theta * n);
    // 垂直方向分量
    vec3 r_out_perp = sqrt(1.0 - r_out_parallel.length_squared()) * (-n);
    return r_out_parallel + r_out_perp;
}



#endif //SOFTRAYTRACING_VEC3_H
