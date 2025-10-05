#include "robot.h"
#include "world.h"
#include<iostream>
using namespace std;

Robot::Robot(): orientation(EAST),
                movement(0),
                foundCoinsNum(0){}

orientation_type Robot::getOrientation() const {
    return orientation;
}

// initial the robot face at east and location at (0,0).
// initial robot movement=0.
// initial robot finds coins number=0.

void Robot::init() {
    robotPosition.set(0,0);
    orientation = EAST;
    movement = 0;
    foundCoinsNum = 0;
}


void Robot::print() const {
    cout << "I am at ";
    robotPosition.print();
    cout << " and I am facing ";

    switch (orientation) {
        case NORTH: cout << "north"; break;
        case SOUTH: cout << "south"; break;
        case EAST: cout << "east"; break;
        case WEST: cout << "west"; break;
        default: cout << "none";
    }
    cout << "." << endl;
}


int Robot::getX() const {
    return robotPosition.getX();
}

int Robot::getY() const {
    return robotPosition.getY();
}

int Robot::getMoves() const {
    return movement;
}

int Robot::getFoundCoins() const {
    return foundCoinsNum;
}

void Robot::incrementCoinsNum() {
    foundCoinsNum++;
}


bool Robot::forward() {
    int currentX = robotPosition.getX();
    int currentY = robotPosition.getY();

    switch (orientation) {
        case NORTH: currentY++; break;
        case SOUTH: currentY--; break;
        case EAST: currentX++; break;
        case WEST: currentX--; break;
    }

    // update the movements the robot moved.
    if (currentX >= 0 && currentX <= MAX_NUM_OF_BOARD && currentY >= 0
        && currentY <= MAX_NUM_OF_BOARD) {
        robotPosition.set(currentX,currentY);
        movement++;
        return true;
    }return false;
}

void Robot::turnCW() {
    switch (orientation) {
        case NORTH: orientation = EAST; break;
        case EAST: orientation = SOUTH; break;
        case SOUTH: orientation = WEST; break;
        case WEST: orientation = NORTH; break;
    }
}

void Robot::turnAntiCW() {
    switch (orientation) {
        case NORTH: orientation = WEST;  break;
        case WEST:  orientation = SOUTH; break;
        case SOUTH: orientation = EAST;  break;
        case EAST:  orientation = NORTH; break;
    }
}


// define zag and zig
// if start from the face to the east.
// down left (bottom) is the starting point at location (0,0)

//step 1, turn face to the north
//step 2, move one step(up one north )
//step 3, turn face to the west, finish with a zag.

bool Robot::zag() {
    if (orientation == EAST) {
        turnAntiCW();

        bool moved = forward(); // (Y+1)

        if (moved) {
            turnAntiCW(); // face to WEST,

        }return moved;

    }return false;
}


// from westEnd to eastEnd.
bool Robot::zig() {
    if (orientation == WEST) {
        turnCW(); //turn to the NORTH

        bool moved = forward(); // (Y+1)

        if (moved) {
            turnCW(); // face to EAST

        }return moved;

    }return false;
}


bool Robot::eastEnd() const {
    return robotPosition.getX() == MAX_NUM_OF_BOARD;
}

bool Robot::westEnd() const {
    return robotPosition.getX() == 0;
}
bool Robot::northEnd() const {
    return robotPosition.getY() == MAX_NUM_OF_BOARD;
}
bool Robot::southEnd() const {
    return robotPosition.getY() == 0;
}


bool Robot::lookForCoin(World &world) {
    for (int i = 0; i < NUMCOIN_POSITION; ++i) {
        const Point& coin_loc = world.getCoin(i);

        if (coin_loc.getX() == robotPosition.getX() &&
            coin_loc.getY() == robotPosition.getY() &&
            coin_loc.getX() != -1)
        {
            world.collCoin(i);
            this->incrementCoinsNum();


            cout << "\n------------------------" << endl;
            cout << "I am at ";
            robotPosition.print();
            cout << "and I found the " << getFoundCoins();

            if (getFoundCoins() == 1) cout << "st";
            else if (getFoundCoins() == 2) cout << "nd";
            else if (getFoundCoins() == 3) cout << "rd";

            cout << " coin! I’m gonna be rich! Yeaaah!" << endl;
            cout << "------------------------\n" << endl;

            return true;
        }
    }return false;
}


