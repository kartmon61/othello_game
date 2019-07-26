//
//  main.cpp
//  othello
//
//  Created by 이진호 on 09/07/2019.
//  Copyright © 2019 이진호. All rights reserved.
//

#include <iostream>

#define NOT_EMPTY 1
#define NOT_ADJACENT 2
#define OUT_OF_SIZE 3
using namespace std;

char ERROR_MSGS[3][255] = {"빈자리가 아닙니다.\n빈자리에 돌을 놔야 합니다.\n","인접한 적군의 돌이 없습니다.\n적군의 돌을 둘러싸야만 합니다.\n","돌의 범위가 벗어났습니다.\n돌이 범위내에 있어야 합니다.\n"};
ostream &oth(ostream &stream){
    stream.width(2);
    stream.fill(' ');
    return stream;
}

class Othello{
    int board[8][8];
    int getOpp(int kind);
    int checkValidity(int y,int x,int kind);
    int checkAdjacency(int y,int x,int kind,int dir);
    void set(int y,int x,int kind,int dir,int res);
    
public:
    Othello() {
        //0으로 초기화
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                board[y][x] = 0;
            }
        }
        board[3][3] = board[4][4] = 1;
        board[4][3] = board[3][4] = 2;
    }
    void viewBoard();
    void score();
    int put(int position, int kind);
};

void Othello::viewBoard(){
    cout << oth << " ";
    for(int x=0;x<8;x++){
        cout << oth << x+1;
    }
    cout << endl;
    
    for(int y=0;y<8;y++){
        cout << oth << y+1;
        for(int x=0;x<8;x++){
            if(board[y][x]==0) cout << oth << " ";
            else if(board[y][x]==1) cout << oth << "O";
            else cout << oth << "X";
        }
        cout << endl;
    }
}



int Othello::getOpp(int kind){
    if(kind == 1) return 2;
    else return 1;
}

int Othello::checkValidity(int y, int x, int kind) {
    
    if(y>7 || y<0 || x>7 || x<0) return OUT_OF_SIZE;
    if (board[y][x] != 0) return NOT_EMPTY;
    int adjacency = 0;
    for (int dir = 0; dir < 8; dir++) {
        int res = checkAdjacency(y, x, kind, dir);
        if (res > 0) {
            adjacency += res; set(y, x, kind, dir, res);
        }
    }
    if (adjacency == 0) return NOT_ADJACENT;
    return 0;
}

int Othello::checkAdjacency(int y, int x, int kind, int dir) {
    int nOppCount = 0;
    int nMyCount = 0;
    while (1) {
        switch (dir) {
            case 0: x--;
                break;
            case 1: x++;
                break;
            case 2: y--;
                break;
            case 3: y++;
                break;
            case 4: x--; y--;
                break;
            case 5: x--; y++;
                break;
            case 6: x++; y--;
                break;
            case 7: x++; y++;
                break;
            default: break;
        }
        if (x < 0 || y < 0 || x>7 || y>7)
            break;
        if (board[y][x] == getOpp(kind))
            nOppCount++;
        else if (board[y][x] == kind) {
            nMyCount++; break;
        }
        else
            break;
    } if (nOppCount > 0 && nMyCount == 1)
        return nOppCount;
    else
        return 0;
}

void Othello::set(int y, int x, int kind, int dir, int res) {
    int nCount = 0;
    while (1) {
        switch (dir) {
            case 0:
                x--;
                break;
            case 1:
                x++;
                break;
            case 2:
                y--;
                break;
            case 3:
                y++;
                break;
            case 4:
                x--;
                y--;
                break;
            case 5:
                x--;
                y++;
                break;
            case 6:
                x++;
                y--;
                break;
            case 7:
                x++;
                y++;
                break;
            default:
                break;
        }
        board[y][x] = kind;
        nCount++;
        if (nCount == res)
            break;
    }
}

int Othello::put(int position, int kind) {
    int x, y; y = position / 10 - 1;
    x = position % 10 - 1;
    int valid = checkValidity(y, x, kind);
    if (valid == 0) {
        board[y][x] = kind;
        return 0;
    }
    else
        return valid;
}


void Othello::score(){
    int nO = 0;
    int nX = 0;
    
    for(int y=0;y<8;y++){
        for(int x=0;x<8;x++){
            if(board[y][x]==1) nO++;
            else if (board[y][x] == 2) nX++;
        }
    }
    
    cout << "'O' : " << nO << endl;
    cout << "'X' : " << nX << endl;
}





int main(int argc, const char * argv[]) {
    Othello othello;
    int input;
    int kind = 0;
    
    while(1){
        
        if(++kind > 2) kind=1;
        
        othello.viewBoard();
        
        if(kind==1) cout << "Enter O position :";
        else cout << "Enter X position :";
        
        cin >> input;
        
        if(input==0) break;
        if(input==99) continue;
        
        int res = othello.put(input, kind);
        
        if(res!=0){
            cout << ERROR_MSGS[res-1]<<endl;
            kind--;
            continue;
        }
    }
    
    othello.score();
    
    return 0;
}
