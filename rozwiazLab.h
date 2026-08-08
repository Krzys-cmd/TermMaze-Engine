#pragma once

#include "plansza.h"
#include "generujLab.h"

class RozwiazLab{
private:
    plansza& board;
public:
    RozwiazLab(plansza& b);
    bool solve(punkt start, punkt koniec);

};
