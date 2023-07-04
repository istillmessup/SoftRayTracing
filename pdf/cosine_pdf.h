//
// Created by istil on 2023/7/4.
//

#ifndef SOFTRAYTRACING_COSINE_PDF_H
#define SOFTRAYTRACING_COSINE_PDF_H

#include "pdf.h"


class cosine_pdf : public pdf {
public:
    explicit cosine_pdf(const vec3& w) { uvw.build_from_w(w); }

    double value(const vec3& direction) const override {
        auto cosine = dot(normalize(direction), uvw.w());
        return (cosine <= 0) ? 0 : cosine / PI;
    }

    vec3 generate() const override {
        return uvw.local(vec3::random_cosine_direction());
    }
public:
    onb uvw;
};


#endif //SOFTRAYTRACING_COSINE_PDF_H
