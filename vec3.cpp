//
// Created by istil on 2023/6/24.
//

#include "vec3.h"
#include "common.h"

void vec3::write_color(std::ostream &out, int samples_per_pixel) {
    // NaN不等于它自己
    if (vec[0] != vec[0]) vec[0] = 0.0;
    if (vec[1] != vec[1]) vec[1] = 0.0;
    if (vec[2] != vec[2]) vec[2] = 0.0;

    auto scale = 1.0 / samples_per_pixel;
    // gamma2矫正
    auto r = sqrt(scale * vec[0]);
    auto g = sqrt(scale * vec[1]);
    auto b = sqrt(scale * vec[2]);
    {
        out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
    }
}

vec3 vec3::random() {
    return {random_double(), random_double(), random_double()};
}

vec3 vec3::random(double min, double max) {
    return {random_double(min, max), random_double(min, max), random_double(min, max)};
}

vec3 vec3::random_normalized_vector() {
    auto a = random_double(0, 2 * PI);
    auto z = random_double(-1, 1);
    auto r = sqrt(1 - z * z);
    return {r * cos(a), r * sin(a), z};
}

vec3 vec3::random_in_normalized_disk() {
    while (true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 vec3::random_cosine_direction() {
    auto r1 = random_double();
    auto r2 = random_double();
    auto z = sqrt(1 - r2);

    auto phi = 2 * PI * r1;
    auto x = cos(phi) * sqrt(r2);
    auto y = sin(phi) * sqrt(r2);

    return {x, y, z};
}

vec3 vec3::random_to_sphere(double radius, double distance_squared) {
    auto r1 = random_double();
    auto r2 = random_double();
    auto z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);

    auto phi = 2 * PI * r1;
    auto x = cos(phi) * sqrt(1 - z * z);
    auto y = sin(phi) * sqrt(1 - z * z);

    return {x, y, z};
}
