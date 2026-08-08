#include "rozwiazLab.h"

#include <queue>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

RozwiazLab::RozwiazLab(plansza& b) : board(b) {}

bool RozwiazLab::solve(punkt start, punkt koniec){
    int  wys = board.getWys();
    int szer = board.getSzer();

    std::queue<punkt> q;
    std::vector<std::vector<bool>> odwiedzone(wys, std::vector<bool>(szer, false));

    std::vector<std::vector<punkt>> rodzic(wys, std::vector<punkt>(szer, {-1,-1}));

    q.push(start);
    odwiedzone[start.y][start.x] = true;
    board.setCell(start.x,start.y,'.');

    int dx[] = {1,-1,0,0};
    int dy[] = {0,0,1,-1};

    bool znaleziony = false;

    while(!q.empty()){
        punkt obecny = q.front();
        q.pop();

        if(obecny.x == koniec.x && obecny.y == koniec.y){
            znaleziony = true;
            break;
        }
        for(int i = 0; i < 4; i++){
            int nx = obecny.x + dx[i];
            int ny = obecny.y + dy[i];

            if(board.isValid(nx,ny) && board.getCell(nx,ny) == plansza::PATH && !odwiedzone[ny][nx]){
                odwiedzone[ny][nx] = true;
                rodzic[ny][nx] = obecny;
                q.push({nx,ny});

                if(!(nx == koniec.x && ny == koniec.y)){
                    board.setCell(nx,ny,'.');
                }

            }
        }
        board.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(15));

    }
    for(int i = 0; i < wys; i++){
        for(int j = 0; j < szer; j++){
            if(board.getCell(j,i) == '.'){
                board.setCell(j,i,plansza::PATH);
            }
        }
    }
    if(znaleziony){
        punkt teraz = koniec;

        while(!(teraz.x == start.x && teraz.y == start.y)){
            board.setCell(teraz.x,teraz.y,plansza::ROUTE);
            teraz = rodzic[teraz.y][teraz.x];

            board.print();
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
        board.setCell(start.x,start.y,plansza::ROUTE);
        board.print();
    }
    return znaleziony;
}

