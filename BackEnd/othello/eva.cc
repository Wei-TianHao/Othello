#include "eva.hpp"

PII eva::UCT(OthelloState root_state, clock_t start_time, int sec) {
    eva::Node root_node = eva::Node(root_state);
    while((clock() - start_time)/ (double) CLOCKS_PER_SEC < sec - 1) {
        int itermax = 2000;
        while(itermax-- > 0) {
            OthelloState state = root_state;
            eva::Node* node = &root_node;
            // cout << "select" << endl;
            // Select
            while (node->untried_moves.size() == 0 && node->children.size() != 0) { //node is fully expanded and non-terminal
                node = node->SelectChild();
                state = node->state;
            }
            // cout << "expand" << endl;
            // Expand
            if (node->untried_moves.size() > 0) {
                PII m = *(next(std::begin(node->untried_moves), rand()%(node->untried_moves.size())));
                state.DoMove(m.first, m.second);
                node = node->AddChild(m, state);
            }
            // cout << "rollout" << endl;
            // Rollout
            unordered_set<PII, pair_hash> moves;
            state.GetAllMoves(moves);

            while (moves.size() > 0) {
                PII m = *(next(std::begin(moves), rand()%(moves.size())));
                state.DoMove(m.first, m.second);
                state.GetAllMoves(moves);
            }

            // cout << "Update" << endl;
            // Update
            while (node != NULL) {
                node->update(node->GetResult());
                node = node->parent;
            }
        }
    }
    eva::Node* ret = root_node.children[0];
    for(auto x:root_node.children) {
        if (x->visits > ret->visits) {
            ret = x;
        }
    }
    return ret->move;
}
PII eva::step(OthelloState state, clock_t start_time, int sec) {
    unordered_set<PII, pair_hash> moves;
    state.GetAllMoves(moves);
    if(moves.size() == 0) {
        return make_pair(-1, -1);
    }
    else{
        PII m = eva::UCT(state, start_time, sec);
        return m;
    }
}
