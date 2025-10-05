#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "robot.h"
#include "world.h"
#include "point.h"

using namespace std;

//clear the whole screen and move the cursor to the top-left corner.
//faster than clear.

#define ANSI_CLEAR_SCREEN "\033[2J\033[1;1H"

void clearScreen() {
    std::cout << ANSI_CLEAR_SCREEN;
    std::cout.flush();
}


bool validate_and_convert(const char* arg, int& result, int min_val = 0, int max_val = MAX_NUM_OF_BOARD) {
    result = atoi(arg);

    if (result < min_val || result > max_val) {
        cerr << "Input Validation Error: Coordinate " << arg << " is outside the valid range ["
                  << min_val << ", " << max_val << "]." << endl;
        return false;
    }
    return true;
}


void displayWorld(const World& world, const Robot& robot) {
    cout << endl;
    cout << "-ROBOT WORLD BOARD-              " << endl;

    for (int y = MAX_NUM_OF_BOARD; y >= 0; --y) {

        for (int x = 0; x <= MAX_NUM_OF_BOARD; ++x) {

            char symbol = '.';

            if (robot.getX() == x && robot.getY() == y) {
                symbol = 'R';
            } else {
                for (int i = 0; i < NUMCOIN_POSITION; ++i) {
                    const Point& coin_loc = world.getCoin(i);

                    if (coin_loc.getX() == x && coin_loc.getY() == y && coin_loc.getX() != 0) {
                        symbol = 'C';
                        break;
                    }
                }
            }
            cout << symbol << " ";
        }
        cout << " " << endl;
    }

    cout << "R = Robot" << endl;
    cout << "C = Coin" << endl;
}


int main(int argc, char* argv[]) {

    if (argc != 7) {
        cerr << "Error: Expected 6 command-line arguments (x1 y1 x2 y2 x3 y3), received " << argc - 1 << "." << endl;
        cerr << "Usage: " << argv[0] << " <coin1-x> <coin1-y> <coin2-x> <coin2-y> <coin3-x> <coin3-y>" << endl;
        return 1;
    }

    World robot_world;
    int coord_value;
    vector<int> coords;


    for (int i = 1; i <= 6; ++i) {

        if (validate_and_convert(argv[i], coord_value)) {
            coords.push_back(coord_value);
        } else {
            return 1;
        }
    }


    for (int i = 0; i < NUMCOIN_POSITION; ++i) {
        robot_world.setOrientation(i, coords[i * 2], coords[i * 2 + 1]);
    }

    Robot explorer;
    explorer.init();

//before while loop, clear the screen
    // cout << "--- Initial Setup ---" << endl;
    robot_world.print();
    displayWorld(robot_world, explorer);


    //move logic: after movement, then clear the screen, and delay.

    while (explorer.getFoundCoins() < NUMCOIN_POSITION) {

        this_thread::sleep_for(chrono::milliseconds(200));
        clearScreen();

        cout << "--- Robot Search Coins ---" << endl;
        cout << "Moves: " << explorer.getMoves() << " | Coins Found: "
             << explorer.getFoundCoins() << endl;

        explorer.print();

        //check if there are more coins.
        bool coin_found_now = explorer.lookForCoin(robot_world);

        // print board
        displayWorld(robot_world, explorer);

        std::cout.flush();

        // when find the coin, show the string.
        if (coin_found_now) {
            this_thread::sleep_for(chrono::milliseconds(100000));
        } else {
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        if (explorer.getFoundCoins() == NUMCOIN_POSITION) break;

        if (explorer.forward()) {
            continue;
        }

        // check if the robot at the eastEnd/westEnd
        if (explorer.getOrientation() == EAST) {
            if (!explorer.zag()) {
                break;
            }
        }else if (explorer.getOrientation() == WEST) {
            if (!explorer.zig()) {
                break;
            }
        }
    }

    unsigned int total_moves = explorer.getMoves();

    clearScreen();
    displayWorld(robot_world, explorer);

    std::cout.flush();

    this_thread::sleep_for(chrono::milliseconds(50));

    cout << "\n--- Record ---" << endl;
    cout << "The robot completes search for coins." << endl;
    cout << "Total coins found: " << explorer.getFoundCoins() << " / " << NUMCOIN_POSITION << "." << endl;
    cout << "The robot moved " << total_moves << " steps." << endl;

    std::cout.flush();

    return 0;
}
