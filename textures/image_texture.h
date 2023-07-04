//
// Created by istil on 2023/6/28.
//

#ifndef SOFTRAYTRACING_IMAGE_TEXTURE_H
#define SOFTRAYTRACING_IMAGE_TEXTURE_H

#include "texture.h"

class image_texture : public texture {
public:
    image_texture(unsigned char* pixels, int a, int b)
        : data(pixels), nx(a), ny(b) {};
    ~image_texture() { delete data; }

    vec3 value(double u, double v, const vec3& p) const override;
public:
    unsigned char* data;
    int nx, ny;
};


#endif //SOFTRAYTRACING_IMAGE_TEXTURE_H
