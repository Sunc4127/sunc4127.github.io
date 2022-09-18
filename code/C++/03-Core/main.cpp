#include <iostream>
using namespace std;
#include <cmath>
#include "header_files/Point.h"
#include "header_files/Circle.h"

void isInCircle(Circle &c, Point &p) {
    double distance =  sqrt(pow((c.getCenter().getX() - p.getX()), 2) +
                            pow((c.getCenter().getY() - p.getY()), 2));

    if (distance == c.getR())
        cout << "On the edge of the circle" << endl;
    else if (distance > c.getR())
        cout << "Outside of the circle" << endl;
    else
        cout << "Inside the circle" << endl;
}

/*
int main() {
    Point p1{};
    p1.setX(5);
    p1.setY(5);

    Point p2{};
    p2.setX(5);
    p2.setY(0);

    Circle c{};
    c.setRadius(5);
    c.setCenter(p2);

    isInCircle(c, p1);
}*/
