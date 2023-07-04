//
// Created by istil on 2023/7/2.
//

#include "onb.h"

void onb::build_from_w(const vec3& vec) {
    axis[2] = normalize(vec);
    vec3 temp = (fabs(w().x()) > 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
    axis[1] = normalize(cross(w(), temp));
    axis[0] = cross(w(), v());
}
