#pragma once
#include "plansza.h"
//#include <vector>

class generujLab{
private:
    plansza& board;
public:
    generujLab(plansza& b);
    void generator(int startoweX, int startoweY);
    std::vector<int> getValidSasiad(punkt obecny) const;
};
