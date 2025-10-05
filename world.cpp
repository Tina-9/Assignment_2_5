//
// Created by Fay on 10/4/25.
//

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
    for (int i = 0; i < NUMCOIN_POSITION; ++i) {
        cout<< "coin " << i + 1 << ": ";
        coinPosition[i].print();
        if (i < NUMCOIN_POSITION - 1) cout <<", ";
    }
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

