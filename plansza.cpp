#include "plansza.h"

#include<iostream>
Board::Board(int x, int y) : boardWidth(x), boardHeight(y) {}

void Board::clear(){
  std::vector<std::vector<char>> grid2(boardHeight, std::vector<char>(boardWidth, WALL));
  grid = grid2;
}

void Board::print(){
 std::cout<<"\033[H";
 for(int i = 0; i < boardHeight; i++){
    for(int j = 0; j < boardWidth; j++){
        if(grid[i][j] == '.'){
          std::cout<<"\033[46m"<<"  "<<"\033[0m";
        }
        else if(grid[i][j] == Board::ROUTE){
          std::cout<<"\033[42m"<<"  "<<"\033[0m";
        }
        else if(grid[i][j] == Board::WALL){
          std::cout<<"\033[48;2;160;160;160m"<<"  "<<"\033[0m";
        }
        else{
          std::cout<<grid[i][j]<<" ";
        }
    }
   std::cout<<"\n";
 }
}

bool Board::setCell(int x, int y, char symbol){
  if(x > 0 && x < boardWidth - 1 && y > 0 && y < boardHeight - 1){
    grid[y][x] = symbol;
    return true;
  }
 return false;
}

bool Board::isValid(int x, int y){
return (x > 0 && x < boardWidth - 1 && y > 0 && y < boardHeight - 1);
}

char Board::getCell(int x, int y){
 if(x >= 0 && x < boardWidth && y >= 0 && y < boardHeight){
    return grid[y][x];
 }
return WALL;
}

int Board::getHeight(){
return boardHeight;
}

int Board::getWidth(){
return boardWidth;
}
