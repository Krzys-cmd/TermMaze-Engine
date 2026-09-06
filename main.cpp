#include <iostream>
#include <thread>
#include <chrono>

#include "plansza.h"
#include "generujLab.h"
#include "rozwiazLab.h"

int main()
{
    std::cout<<"\033[?25l";

    const int width = 25;
    const int height = width;

    Board mazeBoard(width, height);
    mazeBoard.clear();

    GenerateLab gen(mazeBoard);
    gen.generator(1, 1);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    SolveLab solve(mazeBoard);
    Point start{1, 1};
    Point end{width - 2, height - 2};

    solve.solve(start, end);
    return 0;
}
