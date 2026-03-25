#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
// #include <unordered_map>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 4e4 + 10;
const int M = 2e2 + 10;

int n, m;
int T;
int a[N];
int tmp[N];
int L[M], R[M];
int belong[N];
int bucket[N];
int cnt[N][M];
int mode[M][M];
int uni[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    T = sqrt(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tmp[i] = a[i];
    }
    sort(tmp + 1, tmp + n + 1);
    int top = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    for (int i = 1; i <= n; i++) {
        uni[lower_bound(tmp + 1, tmp + top + 1, a[i]) - tmp] = a[i];
        a[i] = lower_bound(tmp + 1, tmp + top + 1, a[i]) - tmp;
    }
    #ifdef __Debug
    for (int i = 1; i <= n; i++) printf("a[%d]=%d\n", i, a[i]);
    #endif
    for (int i = 1; i <= T; i++) {
        L[i] = (i - 1) * (n / T) + 1;
        R[i] = i * (n / T);
    }
    if (R[T] < n) {
        T++;
        L[T] = R[T - 1] + 1;
        R[T] = n;
    }
    for (int i = 1; i <= T; i++) {
        for (int j = L[i]; j <= R[i]; j++) {
            belong[j] = i;
        }
    }
    #ifdef __Debug
    for (int i = 1; i <= n; i++) printf("%d:%d\n", i, belong[i]);
    for (int i = 1; i <= T; i++) printf("%d:%d~%d\n", i, L[i], R[i]);
    #endif
    for (int i = 1; i <= T; i++) {
        int l = L[i], r = R[i];
        for (int j = l; j <= r; j++) cnt[a[j]][i]++;
    }
    for (int i = 1; i <= T; i++) {
        for (int j = 1; j <= n; j++) {
            cnt[j][i] += cnt[j][i - 1];
        }
    }
    for (int i = 1; i <= T; i++) {
        int maxn = 0, id;
        for (int j = i; j <= T; j++) {
            int l = L[j], r = R[j];
            for (int k = l; k <= r; k++) bucket[a[k]]++;
            #ifdef __Debug
            if (i == 3 && j == 3) {
                for (int k = 1; k <= n; k++) printf("bucket[%d]=%d\n", k, bucket[k]);
            }
            #endif
            for (int k = l; k <= r; k++) {
                if (maxn < bucket[a[k]] || (maxn == bucket[a[k]] && a[k] < id)) {
                    maxn = bucket[a[k]];
                    id = a[k];
                }
            }
            mode[i][j] = id;
        }
        for (int j = 1; j <= n; j++) bucket[j] = 0;
    }
    #ifdef __Debug
    for (int i = 1; i <= T; i++) {
        for (int j = i; j <= T; j++) {
            printf("mode[%d][%d]=%d\n", L[i], R[j], uni[mode[i][j]]);
        }
    }
    #endif
    int x = 0;
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        l = (l + x - 1) % n + 1;
        r = (r + x - 1) % n + 1;
        if (l > r) swap(l, r);
        const int QL = belong[l] + 1;
        const int QR = belong[r] - 1;
        int ans = 0, maxn = 0;
        if (QL <= QR) {
            ans = uni[mode[QL][QR]];
            maxn = cnt[mode[QL][QR]][QR] - cnt[mode[QL][QR]][QL - 1];
        }

        #ifdef __Debug
        if (i == 0) for (int j = 1; j <= n; j++) printf("bucket[%d]=%d\n", j, bucket[j]);
        #endif

        if (belong[l] != belong[r]) {
            for (int j = l; j <= R[belong[l]]; j++) bucket[a[j]]++;
            for (int j = L[belong[r]]; j <= r; j++) bucket[a[j]]++;
        }
        else for (int j = l; j <= r; j++) bucket[a[j]]++;

        #ifdef __Debug
        if (i == 3) {
            printf("L=%d R=%d\n", l, r);
            printf("QL=%d QR=%d\n", QL, QR);
            for (int j = 1; j <= n; j++) printf("bucket[%d]=%d\n", j, bucket[j]);
        }
        #endif

        for (int j = l; j <= R[belong[l]]; j++) {
            int tot = bucket[a[j]];
            if (QL <= QR) tot += cnt[a[j]][QR] - cnt[a[j]][QL - 1];
            if (maxn < tot || (maxn == tot && uni[a[j]] < ans)) {
                maxn = tot;
                ans = uni[a[j]];
            }
        }
        for (int j = L[belong[r]]; j <= r; j++) {
            int tot = bucket[a[j]];
            if (QL <= QR) tot += cnt[a[j]][QR] - cnt[a[j]][QL - 1];
            if (maxn < tot || (maxn == tot && uni[a[j]] < ans)) {
                maxn = tot;
                ans = uni[a[j]];
            }
        }
        for (int j = l; j <= R[belong[l]]; j++) bucket[a[j]] = 0;
        for (int j = L[belong[r]]; j <= r; j++) bucket[a[j]] = 0;
        printf("%d\n", ans);
        x = ans;
    }
    return 0;
}