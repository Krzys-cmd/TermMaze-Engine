#pragma once

#include <vector>
#include <random>

struct Point{
    int x;
    int y;
};

class Board{
private:
    int boardWidth;
    int boardHeight;
    std::vector<std::vector<char>> grid;
public:
    static const char WALL = '#';
    static const char PATH = ' ';
    static const char ROUTE = '*';

    Board(int x,int y);

    void clear();
    void print();

    bool setCell(int x, int y, char symbol);
    bool isValid(int x, int y);
    char getCell(int x, int y);

    int getHeight();
    int getWidth();
};
