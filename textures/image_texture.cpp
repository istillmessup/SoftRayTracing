//
// Created by istil on 2023/6/28.
//

#include "image_texture.h"

vec3 image_texture::value(double u, double v, const vec3 &p) const {
    // 如果导入材质失败，返回一个固定颜色
    if (data == nullptr) {
        return {0, 1, 1};
    }
    auto i = static_cast<int>(u * nx);
    auto j = static_cast<int>((1 - v) * ny - 0.001);
    i = (int)clamp(i, 0, nx - 1);
    j = (int)clamp(j, 0, ny - 1);

    auto r = static_cast<int>(data[3 * i + 3 * nx * j]) / 255.0;
    auto g = static_cast<int>(data[3 * i + 3 * nx * j + 1]) / 255.0;
    auto b = static_cast<int>(data[3 * i + 3 * nx * j + 2]) / 255.0;

    return {r, g, b};
}
