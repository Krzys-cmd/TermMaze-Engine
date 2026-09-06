#pragma once

#include "plansza.h"
#include "generujLab.h"

class SolveLab{
private:
    Board& board;
public:
    SolveLab(Board& b);
    bool solve(Point start, Point end);
};
