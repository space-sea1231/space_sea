#include <iostream>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

const int N = 305;
const int M = 2000005;

int T, n, m, k;
int a[M];
deque<int> stk[N];      
int bel[N * 2];         
int stk_of[N * 2];      
bool in_q[N];           
queue<int> free_stk;    
int empty_stk;          

struct Op {
    int type, s1, s2;
};
vector<Op> ans;

void check_free(int s) {
    if (s != empty_stk && stk[s].size() < 2 && !in_q[s]) {
        free_stk.push(s);
        in_q[s] = true;
    }
}

int get_free() {
    while (!free_stk.empty()) {
        int s = free_stk.front();
        if (s == empty_stk || stk[s].size() >= 2) {
            free_stk.pop();
            in_q[s] = false;
        } else {
            return s;
        }
    }
    return 0;
}

void push_card(int s, int c) {
    ans.push_back({1, s, 0});
    if (!stk[s].empty() && stk[s].back() == c) {
        stk[s].pop_back();
        bel[c] = 0;
    } else {
        stk[s].push_back(c);
        bel[c] = s;
        stk_of[c] = s;
    }
    check_free(s);
}

void pop_bottom(int s1, int s2) {
    ans.push_back({2, s1, s2});
    int c = stk[s1].front();
    stk[s1].pop_front();
    stk[s2].pop_front();
    bel[c] = 0;
    check_free(s1);
    check_free(s2);
}

void Solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) cin >> a[i];

    ans.clear();
    while (!free_stk.empty()) free_stk.pop();
    empty_stk = n;
    for (int i = 1; i <= n; i++) {
        stk[i].clear();
        in_q[i] = false;
        if (i < n) check_free(i);
    }
    for (int i = 1; i <= k; i++) {
        bel[i] = stk_of[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int c = a[i];
        if (bel[c]) {
            int s = bel[c];
            if (stk[s].back() == c) {
                push_card(s, c);
            } else {
                push_card(empty_stk, c);
                pop_bottom(empty_stk, s);
            }
        } else {
            int s = get_free();
            if (s != 0) {
                push_card(s, c);
            } else {
                int R = i + 1;
                while (R <= m && a[R] != c && stk[bel[a[R]]].front() != a[R]) {
                    R++;
                }

                if (a[R] == c) {
                    push_card(empty_stk, c);
                    for (int j = i + 1; j < R; j++) {
                        push_card(stk_of[a[j]], a[j]);
                    }
                    push_card(empty_stk, c);
                } else {
                    int S = bel[a[R]];
                    int top_card = stk[S].back();
                    int cnt = 0;
                    for (int j = i + 1; j < R; j++) {
                        if (a[j] == top_card) cnt++;
                    }

                    if (cnt & 1) {
                        push_card(empty_stk, c);
                        for (int j = i + 1; j < R; j++) {
                            push_card(stk_of[a[j]], a[j]);
                        }
                        push_card(S, a[R]); // S 变为空栈
                        int old_empty = empty_stk;
                        empty_stk = S;      // 辅助空栈转移为 S
                        in_q[S] = false;
                        check_free(old_empty);
                    } else {
                        push_card(S, c);
                        for (int j = i + 1; j < R; j++) {
                            if (a[j] == top_card) {
                                ans.push_back({1, empty_stk, 0});
                            } else {
                                push_card(stk_of[a[j]], a[j]);
                            }
                        }
                        push_card(empty_stk, a[R]);
                        pop_bottom(empty_stk, S);
                    }
                }
                i = R; 
            }
        }
    }

    cout << ans.size() << "\n";
    for (const auto& op : ans) {
        if (op.type == 1) {
            cout << "1 " << op.s1 << "\n";
        } else {
            cout << "2 " << op.s1 << " " << op.s2 << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) Solve();
    return 0;
}
/*
The best thing to buy today is a little time for yourself.
今天最值得买下的，是给自己的一点时间
*/