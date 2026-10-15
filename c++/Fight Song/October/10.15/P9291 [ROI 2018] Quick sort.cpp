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
int a[N], b[N], c[N];
vector<pair<int, int> > q;
void Swap(int l, int r) {
    q.emplace_back(make_pair(l, r));
    int cnt = l - 1;
    for (int i = l; i <= r; i++) c[i] = b[i];
    for (int i = l + 1; i <= r; i += 2) b[i] = c[++cnt];
    for (int i = l; i <= r; i += 2) b[i] = c[++cnt];
}
signed main() {
    // freopen("thousand.in", "r", stdin);
    // freopen("thousand.out", "w", stdout);
    srand(time(0));
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x] = i;
    }
    do {
        memcpy(b, a, sizeof(b)); q.clear();
        for (int i = 1; i <= 52; i++) {
            int l = Random(1, n);
            int r = Random(l, n);
            Swap(l, r);
        }
        for (int i = n; i; i--) {
            if (b[i] ^ i) {
                int p = i; while (b[p] ^ i) p--;
                while ((p << 1) <= i) Swap(1, p <<= 1);
                if (p ^ i) Swap((p << 1) - i + 1, i);
            }
        }
    }while(q.size() > 7500);
    printf("%d\n", (int)q.size());
    for (int i = q.size() - 1; ~i; i--) printf("%d %d\n", q[i].first, q[i].second);
    return 0;
}