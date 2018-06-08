#include "roxanne.hpp"

int roxanne::UCT(OthelloState root_state, clock_t start_time, int sec) {
    roxanne::Node root_node = roxanne::Node(root_state);
    int iter_cnt = 0;
    while((clock() - start_time)/ (double) CLOCKS_PER_SEC < sec) {
        int itermax = 100;
        while((clock() - start_time)/ (double) CLOCKS_PER_SEC < sec) {
            iter_cnt++;
            OthelloState state = root_state;
            roxanne::Node* node = &root_node;
            // cout << "select" << endl;
            // Select
            while (node->untried_moves.size() == 0 && node->children.size() != 0) { //node is fully expanded and non-terminal
                node = node->SelectChild();
                state = node->state;
            }
            // cout << "expand" << endl;
            // Expand
            if (node->untried_moves.size() > 0) {
                int m = *(next(std::begin(node->untried_moves), rand()%(node->untried_moves.size())));
                state.DoMove(m);
                node = node->AddChild(m, state);
            }
            // cout << "rollout" << endl;
            // Rollout

            while(!state.is_end()) {
                ULL moves = state.get_valid_move_bit();

                if (state.bit_count(moves) > 0) {
                    int m = roxanne::roxanne_choice(moves);
                    state.DoMove(m);
                }
                else {
                    state.skip();
                }
            }

            // cout << "Update" << endl;
            // Update
            double ret = GetResult(state);
            while (node != NULL) {
                node->update(ret);
                node = node->parent;
            }
        }
    }
    cout << "search times: " << iter_cnt << endl;
    roxanne::Node* ret = root_node.children[0];
    for(auto x:root_node.children) {
        cout << "score: " << x->move/8 << ' ' << x->move%8 << ' ' << x->wins << ' ' << x->visits << ' '<< double(x->wins)/x->visits << endl;
        if (x->wins/x->visits > ret->wins/ret->visits) {
            ret = x;
        }

    }
    return ret->move;
}
int roxanne::step(OthelloState state, clock_t start_time, int sec) {
    set<int> moves;
    state.GetAllMoves(moves);
    if(moves.size() == 0) {
        return -1;
    }
    else{
        int m = roxanne::UCT(state, start_time, sec);
        return m;
    }
}

double roxanne::GetResult(OthelloState state) {
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
int roxanne::rand_one(ULL m) {
    int r = rand()%(__builtin_popcountll(m));
    for(int i = 0; i < 64;i++)
    if(m & (1ULL<<(ULL)i)){
        if(r == 0) return i;
         r--;
    }
}
int roxanne::roxanne_choice(ULL mob) {
    ULL corner = 0x8100000000000081ULL;
    if(mob & corner) return roxanne::rand_one(mob & corner);
    ULL center = 0x00003c24243c0000ULL;
    if(mob & center) return roxanne::rand_one(mob & center);
    ULL edge   = 0x3c0081818181003cULL;
    if(mob & edge) return roxanne::rand_one(mob & edge);
    ULL inner  = 0x003c424242423c00ULL;
    if(mob & inner) return roxanne::rand_one(mob & inner);
    ULL buffer = 0x42c300000000c342ULL;
    if(mob & buffer) return roxanne::rand_one(mob & buffer);
    return -1;
}
