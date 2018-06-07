#include "cooper.hpp"

PII cooper::UCT(OthelloState root_state, clock_t start_time, int sec) {
    cooper::Node root_node = cooper::Node(root_state);
    int iter_cnt = 0;
    clock_t time_rec[10] = {0};
    clock_t tmp;
    while((clock() - start_time)/ (double) CLOCKS_PER_SEC < sec) {
        int itermax = 100;
        while((clock() - start_time)/ (double) CLOCKS_PER_SEC < sec) {
            iter_cnt++;
            OthelloState state = root_state;
            cooper::Node* node = &root_node;
            // cout << "select" << endl;
            // Select
            tmp = clock();
            while (node->untried_moves.size() == 0 && node->children.size() != 0) { //node is fully expanded and non-terminal
                node = node->SelectChild();
                state = node->state;
            }
            time_rec[0] += clock() - tmp;
            // cout << "expand" << endl;
            // Expand
            tmp = clock();
            if (node->untried_moves.size() > 0) {
                PII m = *(next(std::begin(node->untried_moves), rand()%(node->untried_moves.size())));
                state.DoMove(m.first, m.second);
                node = node->AddChild(m, state);
            }
            time_rec[1] += clock() - tmp;
            // cout << "rollout" << endl;
            // Rollout
            tmp = clock();
            unordered_set<PII, pair_hash> moves;
            while(!state.is_end()) {
                clock_t tt = clock();
                get_all_moves(state, moves);
                time_rec[5] += clock() - tt;
                if (moves.size() > 0) {
                    
                    clock_t tt = clock();
                    int x = rand()%moves.size();
                    time_rec[6] += clock() - tt;
                    PII m = *(next(std::begin(moves), x));
                    state.DoMove(m.first, m.second);
                }
                else {
                    state.last_player = !state.last_player;
                }
                
            }
            time_rec[2] += clock() - tmp;
            // cout << "Update" << endl;
            // Update
            tmp = clock();
            double ret = GetResult(state);
            while (node != NULL) {
                node->update(ret);
                node = node->parent;
            }
            time_rec[3] += clock() - tmp;
        }
    }
    cout << "time cost for each part:" << endl;
    for(auto x:time_rec) {
        cout << x / (double) CLOCKS_PER_SEC << endl;
    }
    cout << "search rounds: " << iter_cnt << endl;
    cooper::Node* ret = root_node.children[0];
    for(auto x:root_node.children) {
        cout << "score: " << x->move.first << ' ' << x->move.second << ' ' << x->wins << ' ' << x->visits << ' '<< double(x->wins)/x->visits << endl;
        if (x->wins/x->visits > ret->wins/ret->visits) {
            ret = x;
        }
        
    }
    return ret->move;
}
PII cooper::step(OthelloState state, clock_t start_time, int sec) {
    unordered_set<PII, pair_hash> moves;
    get_all_moves(state, moves);
    if(moves.size() == 0) {
        return make_pair(-1, -1);
    }
    else{
        PII m = cooper::UCT(state, start_time, sec);
        return m;
    }
}

double cooper::GetResult(OthelloState state) {
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
    if(a > b) return 1;
    if(b > a) return 0;
    return 0.5;
}

void cooper::get_all_moves(OthelloState &state, unordered_set<PII, pair_hash> &moves) {
    state.GetAllMoves(moves);
    return;
    PULL key = make_pair(state.board_empty, state.board);
    auto search = cooper::memory.find(key);
    if(search != cooper::memory.end()) {
        moves = search->second;
        exit(0);
    }
    else {
        state.GetAllMoves(moves);
        cooper::memory[key] = moves;
    }
}
