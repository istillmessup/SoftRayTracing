//
// Created by istil on 2023/6/30.
//

#include "box.h"

box::box(const vec3 &p0, const vec3 &p1, const shared_ptr<material>& ptr) {
    box_min = p0;
    box_max = p1;

    sides.add(make_shared<rectangle>(Z, p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
    sides.add(make_shared<rectangle>(Z, p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

    sides.add(make_shared<rectangle>(Y, p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
    sides.add(make_shared<rectangle>(Y, p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

    sides.add(make_shared<rectangle>(X, p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
    sides.add(make_shared<rectangle>(X, p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
}

