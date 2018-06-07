#include<bits/stdc++.h>
#include<ctime>
#include "OthelloState.hpp"
#include "naive.hpp"
#include "cooper.hpp"

using namespace std;
#define ULL unsigned long long
int main(int argc,char **argv) {
    
    string board = argv[1];
    string player = argv[2];
    string version = argv[3];

    // cout << board <<endl;
    // cout << player <<endl;
    // cout << version <<endl;
    ULL emp = 0, ply = 0;

    int sz = (int)sqrt((board.length()+1)/2);
    bool last_player = false;
    for(int i = 0; i < sz; i++) 
        for(int j = 0; j < sz; j++) {
            char c = board[(i*sz+j)*2];
            if(c == 'W' || c == 'B'){
                emp |= 1ULL << ((ULL)i*sz+j);
            }
            if(c == 'B')
                ply |= 1ULL << ((ULL)i*sz+j);
        }
    if (player == "W") 
        last_player = true;
    else
        last_player = false;

    OthelloState state = OthelloState(sz, emp, ply, last_player);
    int m;
    clock_t start_time = clock();
    int time_limit = 2;
    if(version == "naive") {
        m = naive::step(state, start_time, time_limit);
    }
    else if(version == "cooper") {
        m = cooper::step(state, start_time, time_limit);

    }
    // state.DoMove(m.first, m.second);
    // state.ShowBoard();
    printf("%d %d\n", m / sz, m % sz);
    return 0;
}