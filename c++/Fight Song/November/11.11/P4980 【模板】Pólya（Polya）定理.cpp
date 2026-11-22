#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int Mod = 1e9 + 7;

int T;
int n;

int Pow(int a, int b) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = (ll)sum * a % Mod;
        a = (ll)a * a % Mod;
        b >>= 1;
    }
    return sum;
}
int Phi(int x) {
    int rev = x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i) continue;
        rev -= rev / i;
        while (x % i == 0) x /= i;
    }
    if (x > 1) rev -= rev / x;
    return rev;
}
void Solve() {
    cin >> n;
    int ans = 0;
    for (int i = 1; i * i <= n; i++) {
        // cerr<<i<<'\n';
        if (n % i) continue;
        ans = (ans + (ll)Pow(n, i) * Phi(n / i) % Mod) % Mod;
        if (i * i != n) ans = (ans + (ll)Pow(n, n / i) * Phi(i) % Mod) % Mod;
        // while (i ^ 1 && lim % i == 0) lim /= i;
    }
    printf("%lld\n", (ll)ans * Pow(n, Mod - 2) % Mod);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) Solve();
    return 0;
}
/*
那画面千年后依旧 只是定格在小时候
我们手牵手 时间却偷偷溜走
来不及停留 等不到回头 我们已东奔西走
只是我们都茫然的接受
想回到那个小时候 我们在大树下守侯
静静的听着风声笑我们无忧
期待着快快的长大 长大后就可以自由
只有现在才明白那感受
想回到那个小时候 糖葫芦都已经足够
小小的星球却能装满整个宇宙
只想要回到小时候 回到最纯真的年头
无奈中伴着一些内疚
想回到那个小时候 我们在大树下守侯
静静的听着风声笑我们无忧
期待着快快的长大 长大后就可以自由
只有现在才明白那感受
想回到那个小时候 糖葫芦都已经足够
小小的星球却能装满整个宇宙
只想要回到小时候 回到最纯真的年头
无奈中伴着一些内疚
我真的好想回到小时候
*/