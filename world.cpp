#include "world.h"
#include <iostream>
#include "robot.h"
using namespace std;


void World::setOrientation(int i, int x, int y) {
    if (i >= 0 && i < NUMCOIN_POSITION) {
        coinPosition[i].set(x,y);
    }
}

void World::print() const {
    cout << "Coins Locations are: ";
    bool first = true;
    for (int i = 0; i < NUMCOIN_POSITION; ++i) {
        // Only print coins that have NOT been collected (x != -1)
        if (coinPosition[i].getX() != -1) {
            if (!first) cout <<", ";
            cout<< "coin " << i + 1 << ": ";
            // Prints coordinate, requires Point::print() to not add endl
            coinPosition[i].print();
            first = false;
        }
    }
    // End the line after printing all coins
    cout << std::endl;
}

const Point& World::getCoin(int i) const {
    return coinPosition[i];
}

void World::collCoin(int i) {
    if ( i >=0 && i < NUMCOIN_POSITION) {
        coinPosition[i].set(-1,-1);
    }
}

// Function to randomly place coins on the board
void World::randomlyPlaceCoins(int max_board_size) {
    // Seed the random number generator
    srand(time(0));
    for (int i = 0; i < NUMCOIN_POSITION; ++i) {
        int x, y;
        bool unique = false;
        while (!unique) {
            // Generate coordinates within the board size (0 to max_board_size, inclusive)
            x = rand() % (max_board_size + 1);
            y = rand() % (max_board_size + 1);

            // Rule: Avoid initial robot positions: Player at (0,0) and Computer at (max_board_size, max_board_size)
            if ((x == 0 && y == 0) || (x == max_board_size && y == max_board_size)) {
                continue;
            }

            // Check for overlap with already placed coins
            unique = true;
            for (int j = 0; j < i; ++j) {
                if (coinPosition[j].getX() == x && coinPosition[j].getY() == y) {
                    unique = false;
                    break;
                }
            }
        }
        // Set the unique and valid position for the new coin
        coinPosition[i].set(x, y);
    }
}
