//
// Created by Cheng Sun on 2022/8/22.
//

#ifndef INC_03_CORE_CIRCLE_H
#define INC_03_CORE_CIRCLE_H

#include <iostream>
using namespace std;
#include "Point.h"

class Circle {
private:
    int radius;

    // 在类中，可以让另一个类 作为本类中的成员
    Point center;

public:
    void setRadius(int r);

    int getR() const;

    void setCenter(Point c);

    Point getCenter() const;
};
#endif //INC_03_CORE_CIRCLE_H
