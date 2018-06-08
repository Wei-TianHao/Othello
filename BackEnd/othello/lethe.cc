#include "lethe.hpp"

int lethe::UCT(OthelloState root_state, clock_t start_time, int sec) {
    lethe::Node root_node = lethe::Node(root_state);
    int iter_cnt = 0;
    unordered_map<int, double> last_score;
    while((clock() - start_time)/ (double) CLOCKS_PER_SEC < sec) {
        int itermax = 1000;
        while(itermax--) {
            iter_cnt++;
            OthelloState state = root_state;
            lethe::Node* node = &root_node;
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
                    int m;
                    if(state.bit_count(state.board_empty) > 50) {
                        m = lethe::rand_one(moves);
                    }
                    else {
                        m = lethe::lethe_choice(moves);
                    }
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
        double max_gap = 0;
        for(auto x:root_node.children) {
            if(last_score.count(x->move))
                max_gap = max(max_gap, abs(x->wins/x->visits - last_score[x->move]));
            else
                max_gap = max(max_gap, abs(x->wins/x->visits));
            last_score[x->move] = x->wins/x->visits;
        }
        if(max_gap < 1e-4) break;

    }
    cout << "search times: " << iter_cnt << endl;
    lethe::Node* ret = root_node.children[0];
    for(auto x:root_node.children) {
        cout << "score: " << x->move/8 << ' ' << x->move%8 << ' ' << x->wins << ' ' << x->visits << ' '<< double(x->wins)/x->visits << endl;
        if (x->wins/x->visits > ret->wins/ret->visits) {
            ret = x;
        }
    }
    return ret->move;
}
int lethe::step(OthelloState state, clock_t start_time, int sec) {
    set<int> moves;
    state.GetAllMoves(moves);
    if(moves.size() == 0) {
        return -1;
    }
    else{
        int m = lethe::UCT(state, start_time, sec);
        return m;
    }
}

double lethe::GetResult(OthelloState state) {
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
int lethe::rand_one(ULL m) {
    int r = rand()%(__builtin_popcountll(m));
    for(int i = 0; i < 64;i++)
    if(m & (1ULL<<(ULL)i)){
        if(r == 0) return i;
         r--;
    }
}
int lethe::lethe_choice(ULL mob) {
    ULL corner = 0x8100000000000081ULL;
    if(mob & corner) return lethe::rand_one(mob & corner);
    ULL center = 0x00003c24243c0000ULL;
    if(mob & center) return lethe::rand_one(mob & center);
    ULL edge   = 0x3c0081818181003cULL;
    if(mob & edge) return lethe::rand_one(mob & edge);
    ULL inner  = 0x003c424242423c00ULL;
    if(mob & inner) return lethe::rand_one(mob & inner);
    ULL buffer = 0x42c300000000c342ULL;
    if(mob & buffer) return lethe::rand_one(mob & buffer);
    return -1;
}
