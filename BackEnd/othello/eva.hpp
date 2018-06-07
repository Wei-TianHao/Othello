#ifndef EVA_H
#define EVA_H
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<queue>
#include <ctime>

#include "OthelloState.hpp"
using namespace std;
namespace eva
{

class Node {
public:
    vector<Node*> children;
    Node* parent;
    OthelloState state;
    double wins = 0;
    int visits = 0;
    unordered_set<PII, pair_hash> untried_moves;
    PII move;
    Node(OthelloState _state, PII _move = make_pair(-1,-1), Node* parent_node=NULL) {
        parent = parent_node;
        state = _state;
        move = _move;
        state.GetAllMoves(untried_moves);
    }
    
    inline double UCB(Node *a) {
        return a->wins / a->visits + sqrt(2 * log(visits)/a->visits);
    }
    Node* SelectChild() {
        Node* ret = children[0];
        for(auto c: children) {
            if (!state.last_player && UCB(ret) < UCB(c)) {
                ret = c;
            }
            else if (state.last_player && UCB(ret) > UCB(c)) {
                ret = c;
            }
        }
        return ret;
    }

    Node* AddChild(PII m, OthelloState _state) {
        Node *n = new Node(_state, m, this);
        children.push_back(n);
        untried_moves.erase(m);
        return n;
    }

    void update(double result) {
        visits += 1;
        wins += result;
    }

    inline bool inBound(int x, int y) {
        return x >= 0 && x < state.sz && y >= 0 && y < state.sz;
    }

    inline void checkStable(int ply, int x, int y, queue<PII> &q, long long &stb) {
        if(state.getbit(x, y) != ply) return;
        if (!inBound(x, y)) return;
        if(stb & (1 << ((x * state.sz) + y))) return;
        int cnt = 0;
        for(int dx = -1; dx < 2; dx += 2) {
            for(int dy = -1; dy < 2; dy += 2) {
                int nx = x + dx, ny = y + dy;
                if(!inBound(nx, ny) || (stb & (1 << ((nx * state.sz) + ny))) > 0)
                    cnt ++;
            }
        }
        if(cnt < 2) return;
        q.push(make_pair(x, y));
        stb |= 1 << ((x * state.sz) + y);
    }

    int GetStablePiece(int ply) {
        queue<PII> q;
        long long stb = 0;
        checkStable(ply, 0, 0, q, stb);
        checkStable(ply, 0, state.sz-1, q, stb);
        checkStable(ply, state.sz-1, 0, q, stb);
        checkStable(ply, state.sz-1, state.sz-1, q, stb);
        
        while(!q.empty()) {
            PII m = q.front();
            q.pop();
            int x = m.first, y = m.second;
            checkStable(ply, x-1, y, q, stb);
            checkStable(ply, x+1, y, q, stb);
            checkStable(ply, x, y-1, q, stb);
            checkStable(ply, x, y+1, q, stb);
        }
        int ret = 0;
        for(int i = 0; i < state.sz * state.sz; i++)
            if(stb & (1 << i)) ret++;
        return ret;
    }
    double GetResult() {
        long long emp = state.board_empty;
        long long ply = state.board;
        int a = 0, b = 0;
        for(int i = 0; i < state.sz * state.sz; i++) {
            if (emp & 1) {
                if(ply & 1) a++;
                else b++;
            }
            emp >>= 1;
            ply >>= 1;
        }

        //count stable piece
        
        a += 5 * GetStablePiece(1);
        b += 5 * GetStablePiece(0);

        if(a + b == 0) return 0.5;
        return a / (a + b);
    }
};


PII UCT(OthelloState , clock_t, int);
PII step(OthelloState, clock_t, int);
    
}
#endif
