/*
输入：灯数 n、每盏灯所需的已亮邻居数 c[i]。
输出：合法排列数，对 998244353 取模。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 5005, MOD = 998244353;
int n, f[MAXN], g[MAXN];

int main(){
    freopen("light.in", "r", stdin);
    freopen("light.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    f[0] = 1;
    for (int i = 1; i <= n; i++){
        int c;
        cin >> c;
        fill(g, g + i + 1, 0);
        // 新建一块、接到一端、连接两个有序选择的块。
        for (int j = 0; j < i; j++){
            if (f[j] == 0) continue;
            if (c == 0) g[j + 1] = (g[j + 1] + f[j]) % MOD;
            if (c <= 1) g[j] = int((g[j] + 2LL * j * f[j]) % MOD);
            if (j >= 2) g[j - 1] = int((g[j - 1] + ll(j) * (j - 1) * f[j]) % MOD);
        }
        copy(g, g + i + 1, f);
    }
    cout << f[1] << '\n';
    return 0;
}
