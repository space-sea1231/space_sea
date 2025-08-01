#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <unordered_map>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 4e4 + 10;

int n, m;
int T;
int a[N];
int bucket[N];
vector<int> pos[N];
unordered_map<int, int> ump;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    T = sqrt(n * log2(n));
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (ump[a[i]] == 0) ump[a[i]] = i;
        pos[ump[a[i]]].emplace_back(i);
    }
    for (int i = 1; i <= (ceil(double)n / T); i++) {
        int l = (i - 1) * T + 1;
        int r = min(i * T, n);
        for (int j = l; j <= r; i++) {
            bucket[ump[a[j]]]++;
        }
        int id = 0, maxn = 0;
        for (int j = 1; j <= n; j++) {
            if (maxn < bucket[j])
        }
    }
    return 0;
}
/*
3e5 1e9
/ 1 2 3
1 _ _ _
2 _ _ _
3 _ _ _
*/