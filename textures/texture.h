//
// Created by istil on 2023/6/27.
//

#ifndef SOFTRAYTRACING_TEXTURE_H
#define SOFTRAYTRACING_TEXTURE_H

#include "../common.h"

class texture {
public:
    virtual vec3 value(double u, double v, const vec3& p) const = 0;
};


#endif //SOFTRAYTRACING_TEXTURE_H
