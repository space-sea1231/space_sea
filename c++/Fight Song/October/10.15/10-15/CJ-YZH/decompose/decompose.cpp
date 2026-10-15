#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;
const int Mod = 1e9 + 7;

int k, n;
ll l;
int pw[N], invpw[N];
char c[N];
queue<int> q;
int Pow(int a, ll b) {
    int sum = 1;
    while (b) {
        if (b & 1LL) sum = (ll)sum * a % Mod;
        a = (ll)a * a % Mod;
        b >>= 1LL;
    }
    return sum;
}
int C(int n, int m) { return (ll)pw[n] * invpw[m] % Mod * invpw[n - m] % Mod; }

signed main() {
    freopen("decompose.in", "r", stdin);
    freopen("decompose.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = (ll)pw[i - 1] * i % Mod;
    invpw[N - 1] = Pow(pw[N - 1], Mod - 2), invpw[0] = 1;
    for (int i = N - 2; i; i--) invpw[i] = (ll)invpw[i + 1] * (i + 1) % Mod;
    cin >> k >> n >> l;
    for (int i = 1; i <= n; i++) cin >> c[i];
    // int cnt = 0, tot = 0, ans = 1, lst = 0;
    int cnt = 0, ans = 1;
    // for (int i = 1; i <= n; i++) {
    //     if (tot == 0) {
    //         tot = (q.front() - lst) / (k + 1) * k;
    //         lst = q.front();
    //         q.pop();
    //     }
    //     if (c[i] == 'M') {
    //         if (i != 1) {
    //             // cerr << i << " " << tot << " " << min(cnt, k) << "\n";
    //             ans = (ll)ans * C(tot, min(cnt, k)) % Mod;
    //             // if (tot < min(cnt, k)) cerr << tot << " " << min(cnt, k) << "\n";
    //         }
    //         cnt += k;
    //     }
    //     if (c[i] == 'O') cnt--, tot--;
    // }

    for (int i = n; i; i--) {
        if (c[i] == 'M') {
            // cerr << i << " " << tot << " " << min(cnt, k) << "\n";
            ans = (ll)ans * C(cnt, k) % Mod;
            // if (tot < min(cnt, k)) cerr << tot << " " << min(cnt, k) << "\n";
            cnt -= k;
        }
        if (c[i] == 'O') cnt++;
    }
    // if ()
    // cerr << pw[2] << " " << invpw[0] << " " << invpw[2] << "\n";
    // cerr << Pow(pw[2], Mod - 2) << "\n";
    printf("%d\n", Pow(ans, l));
    return 0;
}

/*
梦境和现实的屏障...消失了？不对、不对、不对对对对对对对？？？我在梦中？不对在现实实实
为什么我在梦中在现实在哪里哪里哪里？！？

若不是你突然闯进我生活
我怎会把死守的寂寞放任了
说不痛苦那是假的
毕竟我的心也是肉做的
你离开时我心里的彩虹
就变成灰色
说不心酸那是假的
如果我真的没那么爱过
爱着一个没有灵魂的人
世界都是黑色
若不是你突然闯进 我生活
我怎会把死守的寂寞 放任了
爱我的话你都说
爱我的事你不做
我却把甜言蜜语
当做你爱我的躯壳
你的悲伤难过我不参破
我也会把曾经的且过 当施舍
不去计较你太多
从此你在我心里
只剩绿色
说很快活那是假的
你的名字依然那么深刻
每个字都刺穿我的心脏
那鲜明的痛是红色
若不是你突然闯进 我生活
我怎会把死守的寂寞 放任了
爱我的话你都说
爱我的事你不做
我却把甜言蜜语
当做你爱我的躯壳
你的悲伤难过我不参破
我也会把曾经的且过 当施舍
不去计较你太多
从此你在我心里
只剩绿色
呼
若不是你突然闯进 我生活
我怎会把死守的寂寞 放任了
爱我的话你都说
爱我的事你不做
我却把甜言蜜语
当做你爱我的躯壳
若不是你突然闯进 我生活
我怎会把死守的寂寞 放任了
爱我的话你都说
爱我的事你不做
我却把甜言蜜语
当做你爱我的躯壳
你的悲伤难过我不参破
我也会把曾经的且过 当施舍
若不是你突然闯进 我生活
我怎会把死守的寂寞 放任了
爱我的话你都说
爱我的事你不做
我却把甜言蜜语
当做你爱我的躯壳 
*/