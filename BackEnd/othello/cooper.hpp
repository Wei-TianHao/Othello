#ifndef COOPER_H
#define COOPER_H
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<boost/functional/hash.hpp>
#include<unordered_map>
#include<ctime>
#include"OthelloState.hpp"
using namespace std;
namespace cooper
{

static unordered_map<PULL, unordered_set<PII, pair_hash>, boost::hash<pair<ULL, ULL> > > memory;

class Node {
public:
    vector<Node*> children;
    Node* parent;
    OthelloState state;
    double wins = 0;
    int visits = 0;
    double ucb_coe = 0.5;
    unordered_set<PII, pair_hash> untried_moves;
    PII move;

    Node(OthelloState _state, PII _move = make_pair(-1,-1), Node* parent_node=NULL) {
        parent = parent_node;
        state = _state;
        move = _move;
        state.GetAllMoves(untried_moves);
    }
    
    inline double UCB(Node *a) {
        return a->wins / a->visits + ucb_coe * sqrt(2 * log(visits)/a->visits);
    }
    Node* SelectChild() {
        Node* ret = children[0];
        for(auto c: children) {
            if (UCB(ret) < UCB(c)) {
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

    void update(int result) {
        visits += 1;
        if(state.last_player)
            wins += result;
        else 
            wins += (1-result);
    }

};


PII UCT(OthelloState , clock_t, int);
PII step(OthelloState, clock_t, int);
double GetResult(OthelloState);
void get_all_moves(OthelloState&, unordered_set<PII, pair_hash>&);

}
#endif
