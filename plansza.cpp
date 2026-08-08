#include "plansza.h"

#include<iostream>
plansza::plansza(int x, int y) : wymiarXplanszy(x), wymiarYplanszy(y) {}

void plansza::czysc(){
  std::vector<std::vector<char>> grid2(wymiarYplanszy, std::vector<char>(wymiarXplanszy, WALL));
  grid = grid2;
}

void plansza::print(){
 std::cout<<"\033[H";
 for(int i = 0; i < wymiarYplanszy; i++){
    for(int j = 0; j < wymiarXplanszy; j++){
        if(grid[i][j] == '.'){
          std::cout<<"\033[46m"<<"  "<<"\033[0m";
        }
        else if(grid[i][j] == plansza::ROUTE){
          std::cout<<"\033[42m"<<"  "<<"\033[0m";
        }
        else if(grid[i][j] == plansza::WALL){
          std::cout<<"\033[48;2;160;160;160m"<<"  "<<"\033[0m";
        }
        else{
          std::cout<<grid[i][j]<<" ";
        }
    }
   std::cout<<"\n";
 }
}

bool plansza::setCell(int x, int y, char znak){
  if(x > 0 && x < wymiarXplanszy - 1 && y > 0 && y < wymiarYplanszy - 1){
    grid[y][x] = znak;
    return true;
  }
 return false;
}

bool plansza::isValid(int x, int y){
return (x > 0 && x < wymiarXplanszy - 1 && y > 0 && y < wymiarYplanszy - 1);
}

char plansza::getCell(int x, int y){
 if(x >= 0 && x < wymiarXplanszy && y >= 0 && y < wymiarYplanszy){
    return grid[y][x];
 }
return WALL;
}

int plansza::getWys(){
return wymiarYplanszy;
}

int plansza::getSzer(){
return wymiarXplanszy;
}
