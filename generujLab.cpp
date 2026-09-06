#include "generujLab.h"
#include <stack>
#include <chrono>
#include <thread>

GenerateLab::GenerateLab(Board& b) : board(b) {}

std::vector<int> GenerateLab::getValidNeighbor(Point current)const{
   std::vector<int> validNeighbor;
   int dx[4] = {2,-2,0,0};
   int dy[4] = {0,0,2,-2};

   for(int i = 0; i < 4; i++){
    int nx = current.x + dx[i];
    int ny = current.y + dy[i];

    if(board.isValid(nx,ny) && board.getCell(nx, ny) == Board::WALL){
        validNeighbor.push_back(i);
    }
   }
return validNeighbor;
}

void GenerateLab::generator(int startX, int startY){
std::random_device rd;
std::mt19937 gen(rd());
std::stack<Point> s;

Point start = {startX, startY};
board.setCell(start.x, start.y, Board::PATH);
s.push(start);

int dx[4] = {2,-2,0,0};
int dy[4] = {0,0,2,-2};

    while(!s.empty()){
     Point current = s.top();

     std::vector<int> neighbor = getValidNeighbor(current);

         if(!neighbor.empty()){
            std::uniform_int_distribution<int> distrib(0, neighbor.size() - 1);
            int randomIndex = distrib(gen);
            int selectedDirection = neighbor[randomIndex];

            int dirX = dx[selectedDirection];
            int dirY = dy[selectedDirection];

            Point wallBetween = {current.x + dirX / 2, current.y + dirY / 2};
            Point target = {current.x + dirX, current.y + dirY};

            board.setCell(wallBetween.x, wallBetween.y, Board::PATH);
            board.setCell(target.x, target.y, Board::PATH);

            s.push(target);
         }
         else{
            s.pop();
         }
         board.print();

        // std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}
