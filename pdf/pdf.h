//
// Created by istil on 2023/7/4.
//

#ifndef SOFTRAYTRACING_PDF_H
#define SOFTRAYTRACING_PDF_H

#include "../common.h"
#include "../onb.h"
#include "../hittable/hittable.h"

class pdf {
public:
    virtual ~pdf() = default;

    virtual double value(const vec3& direction) const = 0;
    virtual vec3 generate() const = 0;
};


#endif //SOFTRAYTRACING_PDF_H
