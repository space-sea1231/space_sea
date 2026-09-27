#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <set>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 3e5 + 10;

int T;
ll n, k;
int fil[N];
int ans[N];
set<int> s;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    printf("%d\n", T);
    while (T--) {
        cin >> n >> k;
        printf("%lld %lld\n", n, k);
        if (k < n * (n - 1) / 2 || k > (n - 1) * (n - 1)) {
            printf("-1\n");
            continue;
        }
        k -= n * (n - 1) / 2;
        for (int i = 1; i < n; i++) {
            if (k < (ll)i * (i + 1) / 2) {
                for (int j = 1; j < i; j++) fil[j] = i;
                for (int j = i; j < n; j++) fil[j] = j;
                k -= (ll)i * (i - 1) / 2;
                for (int j = i; j && k; j--) fil[j]++, k--;
                break;
            }
        }
        int minn = 1, maxn = 1; ans[1] = 1;
        for (int i = 2; i <= n; i++) s.insert(i);
        for (int i = 1; i < n; i++) {
            if (fil[i] > maxn - minn) {
                int cur = fil[i] + minn;
                maxn = cur;
                s.erase(cur);
                ans[i + 1] = cur;
            } else {
                int cur = *prev(lower_bound(s.begin(), s.end(), maxn));
                ans[i + 1] = cur;
                s.erase(cur);
            }
        }
        for (int i = 1; i <= n; i++) printf("%d ", ans[i]); printf("\n");
        minn = n, maxn = n, ans[1] = n;
        for (int i = 2; i <= n; i++) s.insert(i);
        for (int i = 1; i < n; i++) {
            if (fil[i] > maxn - minn) {
                int cur = maxn - fil[i];
                minn = cur;
                s.erase(cur);
                ans[i + 1] = cur;
            } else {
                int cur = *upper_bound(s.begin(), s.end(), minn);
                ans[i + 1] = cur;
                s.erase(cur);
            }
        }
        for (int i = 1; i <= n; i++) printf("%d ", ans[i]); printf("\n");
        // for (int i = 1; i < n; i++) printf("%d ", fil[i]); 
        // printf("\n");
    }
    return 0;
}