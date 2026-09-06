#pragma once

#include "Board.h"
#include "GenerateLab.h"

class SolveLab{
private:
    Board& board;
public:
    SolveLab(Board& b);
    bool solve(Point start, Point end);
};
