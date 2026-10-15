#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <random>
#include <chrono>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());
inline int Random(int l, int r) {return Rand() % (r - l + 1) + l;}
const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 3e3 + 10;

int n;
int a[N], b[N];
int pos[N];
vector<pair<int, int> > q;
void Swap(int l, int r) {
    int cnt = l - 1;
    for (int i = l + 1; i <= r; i += 2) b[++cnt] = a[i];
    for (int i = l; i <= r; i += 2) b[++cnt] = a[i];
    for (int i = l; i <= r; i++) a[i] = b[i], pos[a[i]] = i;
}
signed main() {
    freopen("thousand.in", "r", stdin);
    freopen("thousand.out", "w", stdout);
    srand(time(0));
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    int sn = sqrt(n);
    for (int i = 1; i <= 100; i++) {
        int l = Random(1, n - sn);
        int r = l + sn + Random(0, n - l - sn);
        q.emplace_back(make_pair(l, r));
        Swap(l, r);
    }
    for (int i = 1; i <= n; i++) {
        while (pos[i] != i) {
            int l = (((pos[i] - i + 1) & 1) == 0 ? i : i + 1);
            // printf("%d %d\n", l, pos[i]);
            q.emplace_back(make_pair(l, pos[i]));
            Swap(l, pos[i]);
        }
    }
    printf("%d\n", q.size());
    for (pair<int, int>& cur: q) printf("%d %d\n", cur.first, cur.second);
    return 0;
}