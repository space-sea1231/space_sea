#include <bits/stdc++.h>

using i64 = long long;

#define debug(a) std::cout << #a << '=' << (a) << ' '

template <class T>
inline void chmin(T &x, const T &y) {
    if (x > y) {
        x = y;
    }
}
template <class T>
inline void chmax(T &x, const T &y) {
    if (x < y) {
        x = y;
    }
}

const int N = 200100;

int n, m, k;

struct sub {
    int a;
    i64 b;
    int c;
} seq[N];

int ptr[N];
std::vector<int> buc[N];

i64 tim[N];
int ord[N];

void work() {
    std::cin >> n >> m >> k;
    chmin(k, n);

    for (int i = 1; i <= n; i ++) {
        ptr[i] = 0;
        buc[i].clear();
    }

    for (int i = 1; i <= m; i ++) {
        std::cin >> seq[i].a >> seq[i].b >> seq[i].c;
        buc[seq[i].a].push_back(i);
    }

    std::priority_queue<int> pending;
    for (int i = 1; i <= n; i ++) {
        if (buc[i].size()) {
            pending.push(-buc[i][0]);
        }
    }

    std::priority_queue<std::pair<i64, int>> running; // {评测完成时间，提交编号}
    for (int i = 1; i <= k; i ++) {
        running.push({-0, 0});
    }

    std::vector<int> ans;
    while (running.size()) {
        auto [t, id] = running.top(); running.pop();
        t = -t;

        // debug(t), debug(id) << '\n';

        if (id) {
            int team = seq[id].a;
            if (ptr[team] + 1 < buc[team].size()) {
                ptr[team] ++;
                pending.push(-buc[team][ptr[team]]);
            }
        }

        if (pending.size()) {
            int nid = -pending.top(); pending.pop();

            i64 nt = std::max(t, seq[nid].b) + seq[nid].c;
            running.push({-nt, nid});

            tim[nid] = std::max(t, seq[nid].b);
        }
    }

    for (int i = 1; i <= m; i ++) {
        std::cout << tim[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int T;
    std::cin >> T;

    while (T --) {
        work();
    }

    return 0;
}