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
    char displaySymbol; // NEW: The character used to display the robot ('R', 'C', 'P', etc.)

public:
    Robot();

    // 默认初始化 (兼容旧代码)
    void init();

    // NEW: 初始化机器人的位置、方向和符号 (用于对战或 AI)
    void init(int x_start, int y_start, orientation_type orient, char symbol);

    void print() const;

    void setOrientation(orientation_type orientation);
    orientation_type getOrientation() const;

    int getX() const;
    int getY() const;
    int getMoves() const;
    int getFoundCoins() const;
    void incrementCoinsNum();

    char getSymbol() const; // NEW: Getter for the display symbol (Keep the const)

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

    // NEW: AI move function (even if it's currently a placeholder for the base Robot)
    bool aIMovement(World& world);
};


#endif //ROBOT_H
