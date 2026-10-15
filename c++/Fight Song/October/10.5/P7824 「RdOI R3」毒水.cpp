#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e3 + 20;

int n, k;
bitset<N> a[N];
bool rev[N];
int cnt[N];

int Log(int x) {
    for (int i = 0; i < INF; i++) {
        if ((1 << i) >= x) return i;
    }
    return 0;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k;
    if (n == 1) {printf("2\n");fflush(stdout);printf("1\n");fflush(stdout);return 0;}
    int lg = Log(n);
    int lglg = Log(lg);
    for (int i = lg - 1; ~i; i--) {
        int id = lg - i - 1;
        for (int j = 1; j <= n; j += (1 << i + 1)) {
            for (int k = j; k <= j - 1 + (1 << i) && k <= n; k++) {
                a[id].set(k);
            }
        }
        for (int j = 0; j < lglg; j++) {
            if (id & (1 << j)) {
                a[lg + j] ^= a[id];
            }
        }
    }
    for (int i = lg; i < lg + lglg; i++) a[lg + lglg] ^= a[i];
    for (int i = 0; i <= lg + lglg; i++) {
        printf("1 %d ", (int)a[i].count());
        for (int j = 1; j <= n; j++) {
            if (a[i][j]) printf("%d ", j);
        }
        printf("\n");
    }
    printf("2\n");
    fflush(stdout);
    for (int i = 0; i <= lg + lglg; i++) cin >> rev[i];
    for (int i = lg; i <= lg + lglg; i++) cnt[i] = rev[i] ^ 1;
    for (int i = 0; i < lg; i++) {
        for (int j = 0; j < lglg; j++) {
            if (i & (1 << j)) {
                cnt[lg + j] += rev[i] ^ 1;
            }
        }
    }
    for (int j = lg; j < lg + lglg; j++) cnt[lg + lglg] += rev[j] ^ 1;
    if ((cnt[lg + lglg] & 1) == 0) {
        int rat = 0;
        for (int j = lg; j < lg + lglg; j++) {
            if (cnt[j] & 1) {
                rat += (1 << j - lg);
            }
        }
        rev[rat] ^= 1;
        // cerr << rat << "\n";
    }
    // for (int i = 0; i < lg; i++) printf("%d ", rev[i]); printf("\n");
    int l = 1, r = n;
    for (int i = 0; i < lg; i++) {
        int id = lg - i - 1;
        if (rev[i] ^ 1) r = l + (1 << id) - 1;
        else l = l + (1 << id);
    }
    printf("%d\n", l);
    fflush(stdout);
    return 0;
}