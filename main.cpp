#include <iostream>
#include <thread>
#include <chrono>

#include "plansza.h"
#include "generujLab.h"
#include "rozwiazLab.h"

int main()
{
   std::cout<<"\033[?25l";

    const int szer = 25;
    const int wys = szer;

    plansza pla(szer,wys);
    pla.czysc();

    generujLab gen(pla);
    gen.generator(1, 1);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    RozwiazLab solve(pla);
    punkt start{1, 1};
    punkt meta{szer - 2, wys - 2};

    solve.solve(start, meta);
    return 0;
}
