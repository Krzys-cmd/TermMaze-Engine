#include "rozwiazLab.h"

#include <queue>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

SolveLab::SolveLab(Board& b) : board(b) {}

bool SolveLab::solve(Point start, Point end){
    int height = board.getHeight();
    int width = board.getWidth();

    std::queue<Point> q;
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    std::vector<std::vector<Point>> parent(height, std::vector<Point>(width, {-1,-1}));

    q.push(start);
    visited[start.y][start.x] = true;
    board.setCell(start.x,start.y,'.');

    int dx[] = {1,-1,0,0};
    int dy[] = {0,0,1,-1};

    bool found = false;

    while(!q.empty()){
        Point current = q.front();
        q.pop();

        if(current.x == end.x && current.y == end.y){
            found = true;
            break;
        }
        for(int i = 0; i < 4; i++){
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if(board.isValid(nx,ny) && board.getCell(nx,ny) == Board::PATH && !visited[ny][nx]){
                visited[ny][nx] = true;
                parent[ny][nx] = current;
                q.push({nx,ny});

                if(!(nx == end.x && ny == end.y)){
                    board.setCell(nx,ny,'.');
                }

            }
        }
        board.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(15));

    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(board.getCell(j,i) == '.'){
                board.setCell(j,i,Board::PATH);
            }
        }
    }
    if(found){
        Point current = end;

        while(!(current.x == start.x && current.y == start.y)){
            board.setCell(current.x,current.y,Board::ROUTE);
            current = parent[current.y][current.x];

            board.print();
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
        board.setCell(start.x,start.y,Board::ROUTE);
        board.print();
    }
    return found;
}
