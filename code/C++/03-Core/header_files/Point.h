//
// Created by Cheng Sun on 2022/8/22.
//

#ifndef INC_03_CORE_POINT_H
#define INC_03_CORE_POINT_H

#include <iostream>
using namespace std;

class Point {
private:
    int x;
    int y;

public:
    int getX() const;

    int getY() const;

    void setX(int number);

    void setY(int number);

};

#endif //INC_03_CORE_POINT_H
