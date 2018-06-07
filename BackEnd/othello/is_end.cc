#include<bits/stdc++.h>
#include<ctime>
#include "OthelloState.hpp"

using namespace std;
#define ULL unsigned long long
int main(int argc,char **argv) {
    
    string board = argv[1];
    
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

    OthelloState state = OthelloState(sz, emp, ply);
    
    printf("%d\n", state.is_end());
    
    return 0;
}