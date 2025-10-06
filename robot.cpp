#include "robot.h"
#include "world.h"
#include<iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Robot::Robot(): orientation(EAST),
                movement(0),
                foundCoinsNum(0),
                displaySymbol('R') {}



void Robot::init() {
    robotPosition.set(0,0);
    orientation = EAST;
    movement = 0;
    foundCoinsNum = 0;
    displaySymbol = 'R';
}

// new position
void Robot::init(int x_start, int y_start, orientation_type orient, char symbol) {
    robotPosition.set(x_start, y_start);
    orientation = orient;
    movement = 0;
    foundCoinsNum = 0;
    displaySymbol = symbol;
}


void Robot::print() const {
    cout << "I am at ";
    robotPosition.print();
    cout << "I am facing ";

    switch (orientation) {
        case NORTH: cout << "north"; break;
        case SOUTH: cout << "south"; break;
        case EAST: cout << "east"; break;
        case WEST: cout << "west"; break;
        default: cout << "none";
    } cout << "." << endl;
}


// Getters and Setters
orientation_type Robot::getOrientation() const {
    return orientation;
}

void Robot::setOrientation(orientation_type orientation) {
    this->orientation = orientation;
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

char Robot::getSymbol() const {
    return displaySymbol;
}


bool Robot::forward() {
    int currentX = robotPosition.getX();
    int currentY = robotPosition.getY();
    int newX = currentX;
    int newY = currentY;


    switch (orientation) {
        case NORTH: newY++; break;
        case SOUTH: newY--; break;
        case EAST: newX++; break;
        case WEST: newX--; break;
    }

    if (newX >= 0 && newX <= MAX_NUM_OF_BOARD &&
        newY >= 0 && newY <= MAX_NUM_OF_BOARD)
    {
        robotPosition.set(newX, newY);
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
    }movement++;
}

void Robot::turnAntiCW() {
    switch (orientation) {
        case NORTH: orientation = WEST; break;
        case WEST: orientation = SOUTH; break;
        case SOUTH: orientation = EAST; break;
        case EAST: orientation = NORTH; break;
    }movement++;
}


bool Robot::zag() {

    if (orientation == EAST) {
        turnCW();

        bool moved = forward();

        if (moved) {
            turnCW();
        }return moved;
    }return false;
}



bool Robot::zig() {

    if (orientation == WEST) {
        turnAntiCW();
        bool moved = forward();

        if (moved) {
            turnAntiCW();
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
            cout << ",and I found the " << getFoundCoins();

            if (getFoundCoins() == 1) cout << "st";
            else if (getFoundCoins() == 2) cout << "nd";
            else if (getFoundCoins() == 3) cout << "rd";
            else cout << "th";

            cout << " coin!" << endl;
            cout << "------------------------" << endl;
            return true;
        }
    }return false;
}

bool Robot::aIMovement(World& world) {
    int currentX = robotPosition.getX();
    int currentY = robotPosition.getY();
    int closestX = -1, closestY = -1;
    int minDist = -1;

    for (int i = 0; i < NUMCOIN_POSITION; ++i) {
        const Point& coin_loc = world.getCoin(i);
        int coinX = coin_loc.getX();
        int coinY = coin_loc.getY();

        if (coinX != -1) {

            int dist = abs(currentX - coinX) + abs(currentY - coinY);

            if (minDist == -1 || dist < minDist) {
                minDist = dist;
                closestX = coinX;
                closestY = coinY;
            }
        }
    }


    if (closestX != -1) {
        int targetX = closestX;
        int targetY = closestY;

        bool moved = false;

        if (targetX != currentX) {
            orientation_type targetOrient = (targetX > currentX) ? EAST: WEST;
            setOrientation(targetOrient);
            moved = forward();
        }

        if (!moved && targetY != currentY) {
            orientation_type targetOrient = (targetY > currentY) ? NORTH: SOUTH;
            setOrientation(targetOrient);
            moved = forward();
        }return moved;
    }return false;
}


