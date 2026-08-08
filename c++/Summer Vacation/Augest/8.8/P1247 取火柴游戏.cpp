#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e5 + 10;

int n;
int a[N], maxn[N];
vector<int> q;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    int sum_xor = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum_xor ^= a[i];
        for (int k = 31; k >= 0; k--) {
            if (a[i] & (1 << k)) {
                maxn[i] = k;
                break;
            }
        }
    }
    if (!sum_xor) {printf("lose\n"); return 0;}
    int lim;
    for (int i = 0; i <= 31; i++) {
        if (sum_xor & (1 << i)) {
            q.emplace_back(i);
            lim = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (maxn[i] >= lim && (a[i] & (1 << lim))) {
            int sum = 0;
            for (auto k:q) {
                if (a[i] & (1 << k)) sum += (1 << k);
                else sum -= (1 << k);
            }
            printf("%d %d\n", sum, i);
            for (int j = 1; j <= n; j++) printf("%d ", j == i ? a[j] - sum : a[j]);
            printf("\n"); return 0;
        }
    }
    return 0;
}