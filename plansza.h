#pragma once

#include <vector>
#include <random>

struct punkt{
int x;
int y;
};

class plansza{
private:
    int wymiarXplanszy;
    int wymiarYplanszy;
    std::vector<std::vector<char>> grid;
public:
    static const char WALL = '#';
    static const char PATH = ' ';
    static const char ROUTE = '*';

    plansza(int x,int y);

    void czysc();
    void print();

    bool setCell(int x, int y, char znak);
    bool isValid(int x, int y);
    char getCell(int x, int y);

    int getWys();
    int getSzer();
};
