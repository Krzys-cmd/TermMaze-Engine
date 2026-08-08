#include "generujLab.h"
#include <stack>
#include <chrono>
#include <thread>

generujLab::generujLab(plansza& b) : board(b) {}

std::vector<int> generujLab::getValidSasiad(punkt obecny)const{
   std::vector<int> validSasiad;
   int dx[4] = {2,-2,0,0};
   int dy[4] = {0,0,2,-2};

   for(int i = 0; i < 4; i++){
    int nx = obecny.x + dx[i];
    int ny = obecny.y + dy[i];

    if(board.isValid(nx,ny) && board.getCell(nx, ny) == plansza::WALL){
        validSasiad.push_back(i);
    }
   }
return validSasiad;
}

void generujLab::generator(int startoweX, int startoweY){
std::random_device rd;
std::mt19937 gen(rd());
std::stack<punkt> s;

punkt start = {startoweX, startoweY};
board.setCell(start.x, start.y, plansza::PATH);
s.push(start);

int dx[4] = {2,-2,0,0};
int dy[4] = {0,0,2,-2};

    while(!s.empty()){
     punkt obecny = s.top();

     std::vector<int> sasiad = getValidSasiad(obecny);

         if(!sasiad.empty()){
            std::uniform_int_distribution<int> distrib(0, sasiad.size() - 1);
            int ranINdex = distrib(gen);
            int wybranyKierunek = sasiad[ranINdex];

            int dirX = dx[wybranyKierunek];
            int dirY = dy[wybranyKierunek];

            punkt scianaPomeidzy = {obecny.x + dirX / 2, obecny.y + dirY / 2};
            punkt docelowy = {obecny.x + dirX, obecny.y + dirY};

            board.setCell(scianaPomeidzy.x, scianaPomeidzy.y, plansza::PATH);
            board.setCell(docelowy.x, docelowy.y, plansza::PATH);

            s.push(docelowy);
         }
         else{
            s.pop();
         }
         board.print();

        // std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}
