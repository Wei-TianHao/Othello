#include "cooper.hpp"

int cooper::UCT(OthelloState root_state, clock_t start_time, int sec) {
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
                int m = *(next(std::begin(node->untried_moves), rand()%(node->untried_moves.size())));
                state.DoMove(m);
                node = node->AddChild(m, state);
            }
            time_rec[1] += clock() - tmp;
            // cout << "rollout" << endl;
            // Rollout
            tmp = clock();
            set<int> moves;
            clock_t tt = clock();
            bool flag = !is_end(state);
            time_rec[7] += clock() - tt;
            while(flag) {
                clock_t tt = clock();
                get_all_moves(state, moves);
                time_rec[5] += clock() - tt;
                if (moves.size() > 0) {

                    clock_t tt = clock();
                    int x = rand()%moves.size();
                    int m = *(next(std::begin(moves), x));
                    state.DoMove(m);
                    time_rec[6] += clock() - tt;
                }
                else {
//                    cout << "end? " << state.is_end() << endl;
                    state.GetAllMoves(moves);
//                    cout << "cnt1 " << moves.size() << endl;
                    state.skip();
                    state.GetAllMoves(moves);
//                    cout << "cnt2 " << moves.size() << endl;
                }
                tt = clock();
                flag = !is_end(state);
                time_rec[7] += clock() - tt;
                if(!flag) {
//                    cout <<"========= one round =========" << endl;

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
        cout << "score: " << x->move/8 << ' ' << x->move%8  << ' ' << x->wins << ' ' << x->visits << ' '<< double(x->wins)/x->visits << endl;
        if (x->wins/x->visits > ret->wins/ret->visits) {
            ret = x;
        }

    }
    cout << "move repeat: " << cooper::move_cnt << endl;
    cout << "end repeat: " << cooper::end_cnt << endl;
    return ret->move;
}
int cooper::step(OthelloState state, clock_t start_time, int sec) {
    set<int> moves;
    get_all_moves(state, moves);
    if(moves.size() == 0) {
        return -1;
    }
    else{
        int m = cooper::UCT(state, start_time, sec);
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


bool cooper::is_end(OthelloState &state) {
    PULL key = make_pair(state.board_empty, state.board);
    auto search = cooper::end_map.find(key);
    if(search == cooper::end_map.end()) {
        cooper::end_map[key] = state.is_end();
    }
    else {
        end_cnt++;
    }
    return cooper::end_map[key];
}


void cooper::get_all_moves(OthelloState &state, set<int> &moves) {
    state.GetAllMoves(moves);
    return;

    tuple<ULL,ULL,bool> key = tie(state.board_empty, state.board, state.last_player);
//    cout << "searching... " << endl;
    auto search = cooper::move_map.find(key);

    if(search == cooper::move_map.end()) {
//        cout << "adding... " << endl;
        state.GetAllMoves(moves);
        cooper::move_map[key] = moves;
//        cout << "size: " << cooper::move_map[key].size() << endl;

    } else {
//        cout << "======= found" << endl;
        moves = cooper::move_map[key];
//        cout << "======= size: " << moves.size() << endl;
//        cout << state.board_empty << endl;
        move_cnt ++;
//        if(move_cnt > 3) exit(0);
    }
}
