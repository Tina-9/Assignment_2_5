//
// Created by Fay on 10/4/25.
//

#ifndef POINT_H
#define POINT_H

class Point {
private:
    int x;
    int y;
public:
    Point();
    Point(int x_i, int y_i);

    void print() const;
    void set( int x, int y);

    int getX() const;
    int getY() const;


};

#endif //POINT_H
