#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
int a[2000010];
vector<int> v;

int main() {
    freopen("wo.in", "r", stdin);
    freopen("wo.out", "w", stdout);
    int T;
    cin >> T;
    while (T --> 0) {
        int n;
        cin >> n;
        int ans = 0;
        for (int i = 1; i <= n * 2; i++) cin >> a[i];
        for (int i = 1; i <= n * 2; i++) if (!a[i]) ans++;
        cout << ans << "\n";
    }
    return 0;
}