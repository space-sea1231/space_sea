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
typedef unsigned long long ull;
mt19937_64 Rand(chrono::steady_clock().now().time_since_epoch().count());

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e5 + 10;

int n, m;
// int l[N], r[N];
int cov[N];
ull h[N];
ll ans;


long long findEdges(int n, std::vector<int> l, std::vector<int> r){
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    m = l.size();
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i];
        if (l[i] > r[i]) swap(l[i], r[i]);
        ull rd = Rand();
        cov[l[i]]++, cov[r[i]]--;
        h[l[i]] ^= rd, h[r[i]] ^= rd;
    }
    auto Calc = [&](ll x) {return x * (n - x);};
    for (int i = 1; i < n; i++) cov[i] += cov[i - 1], h[i] ^= h[i - 1];
    // for (int i = 1; i < n; i++) {
    //     printf("%d ", cov[i]);
    // }
    ll maxa = 0, maxb = 0;
    for (int i = 1; i < n; i++) { 
        if (cov[i] == 0) {
            ll v = Calc(i);
            if (maxa < v) {
                maxb = maxa;
                maxa = v;
            } else if (maxb < v) maxb = v;
        }
    }
    if (maxb) ans = 2 * (maxa + maxb);
    for (int i = 1; i < n; i++) if (cov[i] <= 1) ans = max(ans, 2 * Calc(i));

    vector<pair<ull, int> > q;
    for (int i = 1; i < n; i++) q.emplace_back(make_pair(h[i], i));
    sort(q.begin(), q.end());
    for (size_t l = 0; l < q.size();) {
        size_t r = l; while (r < q.size() && q[l].first == q[r].first) r++;
        vector<int> pos; for (size_t k = l; k < r; k++) pos.emplace_back(q[k].second);
        for (size_t i = 1; i < pos.size(); i++) {
            int tar = pos[i] - n / 2;
            size_t idx = lower_bound(pos.begin(), pos.begin() + i, tar) - pos.begin();
            for (size_t t = (idx ? idx - 1:0); t <= idx && t < i; t++) {
                ll len = pos[i] - pos[t];
                if (len > 0) ans = max(ans, 2 * len * (ll)(n - len));
            }
        }
        l = r;
    }
    return ans;
}
/*

*/