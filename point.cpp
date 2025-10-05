//
// Created by Fay on 10/4/25.
//

#include "point.h"
#include <iostream>
using namespace std;

Point::Point(): x(0), y(0){}
Point::Point(int x_i, int y_i): x(x_i),y(y_i){}

void Point::print() const {
    std::cout << "(" << x <<", " << y <<")" << endl;
};
void Point::set(int x, int y) {
    this->x = x;
    this->y = y;
}


int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}



