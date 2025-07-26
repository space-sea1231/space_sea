#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define len(x) int((x).size())

using ll = long long;
using db = long double;

template <typename T>
inline bool ckmin(T &x, const T &y) {
    return y < x && (x = y, true);
}

template <typename T>
inline bool ckmax(T &x, const T &y) {
    return x < y && (x = y, true);
}

constexpr int N = 1e6 + 5;

int n;
bool a[N];
vector<int> ans;

void op(int x) {
    assert(x > 1 && x < n);
    ans.push_back(x);
    a[x - 1] = !a[x - 1] && !a[x];
    a[x + 1] = !a[x + 1] && !a[x];
}

void pr() {
    cout << "0 " << len(ans) << "\n";
    for (int i : ans)
        cout << i << " ";
    cout << "\n";
}

void proc() {
    string s;
    cin >> s, n = len(s), s = " " + s;
    for (int i = 1; i <= n; ++i)
        a[i] = s[i] ^ '0';
    ans.clear();
    if (n <= 2)
        return pr();
    if (n == 3) {
        int x = a[1] + a[2] + a[3];
        op(2);
        int y = a[1] + a[2] + a[3];
        if (x > y)
            ans.clear();
        return pr();
    }
    if (accumulate(a + 1, a + n + 1, 0) >= n - 1)
        return pr();
    if (a[2] == 0) {
        if (a[3])
            op(2);
    } else
        op(2), op(3);
    for (int i = 1; i <= n - 4; ++i) {
        if (a[i])
            continue;
        op(i + 1);
        op(i + 2);
        op(i + 3);
    }
    if (!a[n - 3])
        op(n - 2);
    op(n - 1);
    pr();
}

int main() {
    freopen("shi.in", "r", stdin);
    freopen("shi.out", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        proc();
}
