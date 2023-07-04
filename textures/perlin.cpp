//
// Created by istil on 2023/6/28.
//

#include "perlin.h"

double trilinear_interp(vec3 c[2][2][2], double u, double v, double w) {
    auto uu = u * u * u * (u * (u * 6 - 15) + 10);
    auto vv = v * v * v * (v * (v * 6 - 15) + 10);
    auto ww = w * w * w * (w * (w * 6 - 15) + 10);
    auto accum = 0.0;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                // 顶点到插值点的向量。为了求投影
                vec3 weight_v(u - i, v - j, w - k);
                accum += (i * uu + (1 - i) * (1 - uu))
                        * (j * vv + (1 - j) * (1 - vv))
                        * (k * ww + (1 - k) * (1 - ww))
                        * dot(normalize(c[i][j][k]), weight_v);
            }
        }
    }

    return accum;
}

double perlin::noise(const vec3 &p) const { /* NOLINT */
    auto u = p.x() - floor(p.x());
    auto v = p.y() - floor(p.y());
    auto w = p.z() - floor(p.z());

    int i = floor(p.x());
    int j = floor(p.y());
    int k = floor(p.z());

    // 立方体晶格上各个点的梯度
    vec3 temp_grad[2][2][2];
    for (int di = 0; di < 2; ++di) {
        for (int dj = 0; dj < 2; ++dj) {
            for (int dk = 0; dk < 2; ++dk) {
                // -2 & 255 --> 11111111 11111111 11111111 11111110 & 00000000 00000000 00000000 11111111
                temp_grad[di][dj][dk] = grad[perm[(perm[(perm[(i + di) & 255] + j + dj) & 255] + k + dk) & 255] % 12];
            }
        }
    }

    return trilinear_interp(temp_grad, u, v, w);
}

double perlin::turb(const vec3 &p, int depth) const {
    auto accum = 0.0;
    vec3 temp_p = p;
    auto weight = 1.0;

    for (int i = 0; i < depth; ++i) {
        accum += weight * noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return fabs(accum);
}
