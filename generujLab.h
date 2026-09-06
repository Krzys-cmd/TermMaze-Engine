#pragma once
#include "plansza.h"
//#include <vector>

class GenerateLab{
private:
    Board& board;
public:
    GenerateLab(Board& b);
    void generator(int startX, int startY);
    std::vector<int> getValidNeighbor(Point current) const;
};
