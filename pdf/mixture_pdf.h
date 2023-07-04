//
// Created by istil on 2023/7/4.
//

#ifndef SOFTRAYTRACING_MIXTURE_PDF_H
#define SOFTRAYTRACING_MIXTURE_PDF_H

#include "pdf.h"

class mixture_pdf : public pdf {
public:
    mixture_pdf(const shared_ptr<pdf>& p0, const shared_ptr<pdf>& p1) {
        p.emplace_back(p0);
        p.emplace_back(p1);
    }

    double value(const vec3& direction) const override {
        return 0.5 * p[0]->value(direction) + 0.5 * p[1]->value(direction);
    }

    vec3 generate() const override {
        if (random_double() < 0.5) {
            return p[0]->generate();
        }
        else {
            return p[1]->generate();
        }
    }
public:
    std::vector<shared_ptr<pdf>> p;
};


#endif //SOFTRAYTRACING_MIXTURE_PDF_H
