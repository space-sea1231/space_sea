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

void check(i64 n, std::string s) {
    i64 a = 0, b = 0, c = 0;
    for (char ch : s) {
        if (ch == 'h') {
            a ++;
        } else if (ch == 'd') {
            b += a;
        } else if (ch == 'u') {
            c += b;
        } else {
            assert(0);
        }
    }
    assert(s.size() <= 3001);
    assert(c == n);
}

void work() {
    int n;
    std::cin >> n;

    std::string ans;
    if (n <= 1500 * 1500) {
        int q = n / 1500, r = n % 1500;
        if (r) {
            ans += std::string(r, 'h');
            ans += 'd';
        }
        ans += std::string(1500 - r, 'h');
        ans += std::string(q, 'd');
        ans += 'u';
    } else {
        int r = 1000 - n % 1000;

        assert((n - 999 * r) % 1000 == 0);
        int m = (n - 999 * r) / 1000; // m in [1, 999999]
        int q = (m - 1) / 999, s = (m - 1) % 999 + 1; // q in [0, 1000], s in [1, 999]

        ans += std::string(r, 'h');
        ans += 'd';
        ans += std::string(1000 - r, 'h');
        ans += std::string(q, 'd');
        ans += std::string(999 - s, 'u');
        ans += 'd';
        ans += std::string(s, 'u');
    }

    check(n, ans);
    std::cout << ans << '\n';
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