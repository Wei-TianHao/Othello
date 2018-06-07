#include<bits/stdc++.h>
using namespace std;
#define PII pair<int,int>

struct pair_hash {
    inline std::size_t operator()(const PII & v) const {
        return v.first*31+v.second;
    }
};

class OthelloState {
public:
    long long board_empty = 0;
    long long board = 0;
    int sz;
    bool last_player = false;
    inline long long pos(int &x, int &y) {
        return (1LL << ((long long)x*sz+y));
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
        system("clear");
        for(int i = 0; i < sz; i++) {
            for(int j = 0; j < sz; j++) {
                int k = getbit(i, j);
                if (k == -1) printf("+ ");
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
    OthelloState(int size=8) {
        sz = size;
        setbit(sz/2, sz/2, false);
        setbit(sz/2-1, sz/2-1, false);
        setbit(sz/2, sz/2-1, true);
        setbit(sz/2-1, sz/2, true);
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
    //TODO: can be accelerated and make better precision
    double GetResult() {
        long long emp = board_empty;
        long long ply = board;
        int a = 0, b = 0;
        for(int i = 0; i < sz*sz; i++) {
            if (emp & 1) {
                if(ply & 1) a++;
                else b++;
            }
            emp >>= 1;
            ply >>= 1;
        }
        if (!last_player) swap(a, b);
        if(a > b) return 1;
        if(b > a) return 0;
        return 0.5;
    }
    
};

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
            if (UCB(ret) > UCB(c)) {
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
};
PII UCT(OthelloState root_state, int itermax) {
    Node root_node = Node(root_state);
    while(itermax-- > 0) {
        OthelloState state = root_state;
        Node* node = &root_node;
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
            node->update(node->state.GetResult());
            node = node->parent;
        }
    }

    Node* ret = root_node.children[0];
    for(auto x:root_node.children) {
        if (x->visits > ret->visits) {
            ret = x;
        }
    }
    return ret->move;
}
int main() {
    OthelloState state = OthelloState(8);
    state.ShowBoard();
    unordered_set<PII, pair_hash> moves;
    state.GetAllMoves(moves);
    // for(auto m: moves) cout << m.first << " " << m.second << endl;
    // return 0;
    while (moves.size() > 0) {
        if (state.last_player) {
            int x, y;
            cin >> x >> y;
            while(not state.DoMove(x, y)) {
                cout << "Invalid move" << endl;
                cin >> x >> y;
            }
        }
        else {
            PII m = UCT(state, 100000);
            cout << m.first << " " << m.second << endl;
            state.DoMove(m.first, m.second);
        }
        state.ShowBoard();
        state.GetAllMoves(moves);
    }
    double res = state.GetResult();
    if (!state.last_player) {
        res = 1 - res;
    }
    if(res > 0.9) cout << "Black wins!" << endl;
    else if(res < 0.1) cout << "White wins!" << endl;
    else cout << "Tie!" << endl;
    return 0;
}