//
// Created by istil on 2023/7/4.
//

#ifndef SOFTRAYTRACING_HITTABLE_PDF_H
#define SOFTRAYTRACING_HITTABLE_PDF_H

#include "pdf.h"

#include <utility>


class hittable_pdf : public pdf {
public:
    hittable_pdf(shared_ptr<hittable> p, point3 origin) : ptr(std::move(p)), o(std::move(origin)) {}

    double value(const vec3& direction) const override {
        return ptr->pdf_value(o, direction);
    }

    vec3 generate() const override {
        return ptr->random(o);
    }
public:
    point3 o;
    shared_ptr<hittable> ptr;
};


#endif //SOFTRAYTRACING_HITTABLE_PDF_H
