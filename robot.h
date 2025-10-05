//
// Created by Fay on 10/4/25.
//

#ifndef ROBOT_H
#define ROBOT_H
#include "point.h"
# include "world.h"


const int MAX_NUM_OF_BOARD = 9;
enum orientation_type {
    NORTH, SOUTH, EAST, WEST
};

class Robot {
private:
    Point robotPosition; // save location
    orientation_type orientation; // save direction

    int movement; // the robot made moves
    int foundCoinsNum; // the robot found the number of coins

public:
    Robot();

    void init();
    void print() const;

    void setOrientation(orientation_type orientation);
    orientation_type getOrientation() const;

    int getX() const;
    int getY() const;
    int getMoves() const;
    int getFoundCoins() const;
    void incrementCoinsNum();

    bool forward();
    void turnCW();
    void turnAntiCW();

    bool zag();
    bool zig();

    bool eastEnd() const;
    bool westEnd() const;
    bool northEnd() const;
    bool southEnd() const;


    bool lookForCoin(World &world);

};

#endif //ROBOT_H
