//
// Created by Cheng Sun on 2022/8/22.
//

#include "header_files/Circle.h"

void Circle::setRadius(int r) {
    radius = r;
}

int Circle::getR() const {
    return radius;
}

void Circle::setCenter(Point c) {
    center = c;
}

Point Circle::getCenter() const {
    return center;
}
