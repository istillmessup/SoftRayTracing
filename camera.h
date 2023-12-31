//
// Created by istil on 2023/6/25.
//

#ifndef SOFTRAYTRACING_CAMERA_H
#define SOFTRAYTRACING_CAMERA_H

#include "common.h"

class camera {
public:
    camera() {
        origin = vec3(0.0, 0.0, 0.0);
        lower_left_corner = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
    }
    camera(const vec3& lookfrom, const vec3& lookat, const vec3& vup,
           double fov, double aspect,
           double aperture, double focus_dist) {
        origin = lookfrom;
        lens_radius = aperture / 2;
        // 相机坐标系

        auto theta = degrees_to_radians(fov);
        auto half_height = tan(theta / 2);
        auto half_width = aspect * half_height;
        w = normalize(lookfrom - lookat);
        u = normalize(cross(vup, w));
        v = cross(w, u);

        lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }

    ray get_ray(double s, double t) const {
        vec3 rd = lens_radius * vec3::random_in_normalized_disk();
        vec3 offset = u * rd.x() + v * rd.y();

        return {
                origin + offset,
                lower_left_corner + s * horizontal + t * vertical - origin - offset
                };
    }

public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius{};
};


#endif //SOFTRAYTRACING_CAMERA_H
