#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;

int T;
int n;
int a[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    // freopen("dog.in", "r", stdin);
    // freopen("dog.out", "w", stdout);
    cin >> T;
    while (T--) {
        cin >> n; a[n + 1] = INF;
        bool flag = true;
        int cnt = 0;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) {
            if (a[i] < a[i + 1]) {
                if (a[i] <= cnt) {flag = false; break;}
                cnt++;
            }
        }
        if (flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}//ABC208H