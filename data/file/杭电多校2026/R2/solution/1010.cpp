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

int n, k;
std::string str;

i64 f(int i) {
    return 1ll * i * (i + 1) / 2;
}
i64 f(int i, int j) {
    int u = (i - j) / (j + 1), r = (i - j) % (j + 1);
    return f(u) * (j + 1 - r) + f(u + 1) * r;
}

struct node {
    i64 d;
    int i, j;
    bool operator < (const node &rhs) const {
        return d < rhs.d;
    }
};

void work() {
    std::cin >> n >> k;
    std::cin >> str, str = " " + str;

    std::priority_queue<node> q;
    int x = 0, lose = 0;
    i64 sum = 0;
    for (int i = 1; i <= n; i ++) {
        if (str[i] == '0') {
            x ++;
            sum += 20 + 5 * x;
            lose ++;
        } else {
            if (x) {
                q.push({f(x, 0) - f(x, 1), x, 0});
                x = 0;
            }
        }
    }
    if (x) {
        q.push({f(x, 0) - f(x, 1), x, 0});
    }

    if (k >= lose) {
        std::cout << 0 << '\n';
        return;
    }

    for (int idx = 1; idx <= k; idx ++) {
        auto [d, i, j] = q.top(); q.pop();
        sum -= 20 + 5 * d;
        j ++;
        if (j < i) {
            q.push({f(i, j) - f(i, j + 1), i, j});
        }
    }

    std::cout << sum << '\n';
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

/*
3
10 2
1010101010
11 2
00000000001
25 5
1001100100001100010010001
*/