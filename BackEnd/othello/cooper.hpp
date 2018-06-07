#ifndef COOPER_H
#define COOPER_H
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
#include<boost/functional/hash.hpp>
#include<unordered_map>
#include<ctime>
#include"OthelloState.hpp"
using namespace std;
namespace cooper
{

static unordered_map<tuple<ULL, ULL, bool>, set<int>, boost::hash<tuple<ULL, ULL, bool> > > move_map;
static unordered_map<PULL, bool, boost::hash<pair<ULL, ULL> > > end_map;
static int move_cnt = 0;
static int end_cnt = 0;
class Node {
public:
    vector<Node*> children;
    Node* parent;
    OthelloState state;
    double wins = 0;
    int visits = 0;
    double ucb_coe = 0.5;
    set<int> untried_moves;
    int move;

    Node(OthelloState _state, int _move = -1, Node* parent_node=NULL) {
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

    Node* AddChild(int m, OthelloState _state) {
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


int UCT(OthelloState , clock_t, int);
int step(OthelloState, clock_t, int);
double GetResult(OthelloState);
void get_all_moves(OthelloState&, set<int>&);
bool is_end(OthelloState&);
}
#endif
