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

const int N = 100100;

int n;
int d[N];

std::vector<int> g[N];
int L, R;

int len, seq[N];

int get(int x) {
    int p = g[x].back(); g[x].pop_back();
    return p;
}

bool check() {
    if (L != R / 2 + 1) {
        return 0;
    }

    for (int i = R; i > L; i --) {
        if (g[i].size() < 2) {
            return 0;
        }
    }
    if (g[L].size() != (R & 1 ? 1 : 2)) {
        return 0;
    }
    return 1;
}

void work() {
    std::cin >> n;

    for (int i = 1; i <= n; i ++) {
        std::cin >> d[i];
    }

    if (n == 1) {
        std::cout << "Yes\n";
        return;
    }
    if (n == 2) {
        if (d[1] == 2 && d[2] == 2) {
            std::cout << "Yes\n";
            std::cout << 1 << ' ' << 2 << '\n';
        } else {
            std::cout << "No\n";
        }
        return;
    }

    for (int i = 1; i <= n; i ++) {
        g[i].clear();
    }
    for (int i = 1; i <= n; i ++) {
        g[d[i]].push_back(i);
    }

    L = *std::min_element(d + 1, d + 1 + n);
    R = *std::max_element(d + 1, d + 1 + n);

    if (!check()) {
        std::cout << "No\n";
        return;
    }

    len = 0;
    std::vector<std::pair<int, int>> ans;

    int p = get(R), q = get(R);
    seq[++ len] = p;

    for (int i = R - 1; i > L; i --) {
        int x = get(i), y = get(i);
        seq[++ len] = x;

        ans.push_back({p, x}), p = x;
        ans.push_back({q, y}), q = y;
    }

    if (R & 1) {
        int x = get(L);
        seq[++ len] = x;

        ans.push_back({p, x});
        ans.push_back({q, x});
    } else {
        int x = get(L), y = get(L);
        seq[++ len] = x;

        ans.push_back({p, x});
        ans.push_back({q, y});
        ans.push_back({x, y});
    }

    for (int i = R; i > L; i --) {
        while (g[i].size()) {
            assert(R - i + 2 <= len);
            ans.push_back({get(i), seq[R - i + 2]});
        }
    }

    assert(ans.size() == n - 1);
    std::cout << "Yes\n";
    for (auto [x, y] : ans) {
        std::cout << x << ' ' << y << '\n';
    }
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