#ifndef OTHELLOSTATE_H
#define OTHELLOSTATE_H
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include"rng.h"
using namespace std;
#define ULL unsigned long long
#define PII pair<int,int>
#define PULL pair<ULL, ULL>

struct pair_hash {
    inline std::size_t operator()(const PII & v) const {
        return v.first*31+v.second;
    }
};

class OthelloState {
public:
    ULL board_empty = 0;
    ULL board = 0;
    int sz;
    bool last_player = false;
    // last_player = false, next is black
    // last_player = true,  next is white
    inline ULL pos(int &x, int &y) {
        return (1ULL << ((ULL)x*sz+y));
    }
    inline void setbit(int x, int y, bool k) {
        // cout << x << ' ' << y << ' '<< k << endl;
        board_empty |= pos(x, y);
        if (k)
            board |= pos(x,y);
        else
            board &= ~pos(x,y);
    }
    inline int getbit(int x, int y) {
        return board_empty & pos(x, y) ? (board & pos(x,y))>0 : -1;
    }
    void ShowBoard() {
        unordered_set<PII, pair_hash> xy;
        GetAllMoves(xy);
        // system("clear");
        if(last_player) printf("White next:\n");
        if(!last_player) printf("Black next:\n");
        for(int i = 0; i < sz; i++) {
            for(int j = 0; j < sz; j++) {
                int k = getbit(i, j);
                if (k == -1 && xy.count(make_pair(i,j))) printf("P ");
                else if (k != -1 && xy.count(make_pair(i,j))) printf("X ");
                else if (k == -1) printf("+ ");
                else if (k == 0) printf("○ ");
                else if (k == 1) printf("● ");
                
            }
            printf(" %d\n",i);
        }

        printf("\n");
        for(int i = 0; i < sz; i++)
            printf("%d ",i);
        printf("\n\n");
    }
    OthelloState(int size=8, ULL emp=0, ULL ply=0, bool last = false) {
        sz = size;
        if(emp > 0) {
            board_empty = emp;
            board = ply;
            last_player = last;
        }
        else {
            setbit(sz/2, sz/2, false);
            setbit(sz/2-1, sz/2-1, false);
            setbit(sz/2, sz/2-1, true);
            setbit(sz/2-1, sz/2, true);
        }
    }

    bool inline inboard(int x) {
        return 0 <= x && x < sz;
    }
    int inline flip(int x, int y, int dx, int dy, bool f = true) {
        for(int i = 1; i < sz; i++) {
            if (!inboard(x+dx*i) or !inboard(y+dy*i)) {
                break;
            }
            if (getbit(x+dx*i, y+dy*i) == int(last_player)) {
                if(f) {
                    for(int j = 1; j < i; j++) {
                        setbit(x+dx*j, y+dy*j, last_player);
                    }
                }
                return i-1;
            }
            else if(getbit(x+dx*i, y+dy*i) == -1) {
                break;
            }
        }
        return 0;
    }
    bool LegalMove(int x, int y) {
        if ((board_empty & pos(x,y)) != 0) {
            return false;
        }
        
        last_player = !last_player;
        int cnt = 0;
        for(int i = -1; i < 2; i++)
            for(int j = -1; j < 2; j++){
                cnt += flip(x, y, i, j, false);
                
            }
        last_player = !last_player;
        if (cnt == 0) {
            return false;
        }
        return true;
    }
    void GetAllMoves(unordered_set<PII, pair_hash> &xy) {
        xy.clear();
        for(int i = 0; i < sz; i++) {
            for(int j = 0; j < sz; j++) {
                if (LegalMove(i, j)) {
                    // cout << "legal " << i <<" " << j << endl;
                    xy.insert(make_pair(i, j));
                }
            }
        }
    }
    bool is_end() {
        unordered_set<PII, pair_hash> xy;
        GetAllMoves(xy);
        bool ret = true;
        if(xy.size() > 0) return false;

        last_player = !last_player;
        GetAllMoves(xy);
        if(xy.size() > 0) ret = false;
        last_player = !last_player;
        return ret;
    }
    bool DoMove(int x, int y) {

        if ((board_empty & pos(x,y)) != 0) {
            return false;
        }
        last_player = !last_player;
        int cnt = 0;
        for(int i = -1; i < 2; i++)
            for(int j = -1; j < 2; j++)
                cnt += flip(x, y, i, j, true);
        if (cnt == 0) {
            last_player = !last_player;
            return false;
        }
        setbit(x, y, last_player);
        return true;
    }
    void skip() {
        last_player = !last_player;
    }
    //TODO: can be accelerated and make better precision
    
    
};

#endif
