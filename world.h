#ifndef WORLD_H
#define WORLD_H
#include "point.h"

const int NUMCOIN_POSITION = 3;


class World {
private:
    Point coinPosition[NUMCOIN_POSITION];
public:
    void print () const;
    void setOrientation(int i, int x, int y);

    const Point& getCoin(int i) const;

    void collCoin(int i);

    void randomlyPlaceCoins(int max_board_size);

};

#endif //WORLD_H
