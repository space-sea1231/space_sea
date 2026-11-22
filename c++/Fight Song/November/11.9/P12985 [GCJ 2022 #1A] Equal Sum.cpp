#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 300;

int T;
int n;
int a[N];
bool belong[N], vis[N];
int pos[N];

int Lowbit(int x) { return x & -x; }
void Solve(int cur) {
    int num = 0;
    cin >> n;
    for (int i = 0; i < 30; i++) a[++num] = (1 << i);
    for (int i = 3; i <= (n - 30) * 2 + 1; i += 2) a[++num] = i;
    for (int i = 1; i <= n; i++) printf("%d ", a[i]); printf("\n");
    fflush(stdout);
    for (int i = 1; i <= n; i++) cin >> a[++num];
    sort(a + 1, a + num + 1);
    ll sum1 = 0, sum2 = 0;
    for (int i = num; i; i--) {
        if (sum1 <= sum2) {
            sum1 += a[i];
            belong[i] = false;
            if (Lowbit(a[i]) == a[i]) vis[(int)__lg(a[i])] = false, pos[(int)__lg(a[i])] = i;
        } else {
            sum2 += a[i];
            belong[i] = true;
            if (Lowbit(a[i]) == a[i]) vis[(int)__lg(a[i])] = true, pos[(int)__lg(a[i])] = i;
        }
    }
    ll del = abs(sum1 - sum2);
    for (int i = 29; ~i; i--) {
        if (del & (1 << i)) {
            if (sum1 > sum2) {
                if (vis[i - 1] == false) {
                    vis[i - 1] = true;
                    belong[pos[i - 1]] = true;
                } else {
                    vis[i] = false, vis[i + 1] = true;
                    belong[pos[i]] = false, belong[pos[i + 1]] = true;
                }
            }
        }
    }
    ll tot = 0, tt = 0;
    for (int i = 1; i <= num; i++) if (belong[i]) printf("%d ", a[i]); printf("\n");
    for (int i = 1; i <= num; i++) {
        if (belong[i]) tot += a[i];
        tt += a[i];
    }
    // cerr << tt << " " << tot << "\n";
    fflush(stdout);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    for (int _ = 1; _ <= T; _++) Solve(_);
    return 0;
}
/*
骤雨后斜阳正浓 欲挑灯 旌旗动
去成就一段骁勇
不若此身化千里 快哉风 弦上弓
策马追一道彩虹
楼烦城几场决胜定襄破长平封
汉关路笑尽英雄
辟长空 挽弓 啸入苍穹
沐黄沙 敌阵谁敢与我争高下
风云几度 惊半生戎马
拭铁甲 挥兵破阵 再望断天涯
血雨腥风吻过了伤疤
一世气概与君同 御长风 数峥嵘
再成就一段骁勇
但此去剑指漠北定河朔酩酊中
频传着谁的征程
楼烦城几场决胜 定襄破 长平封
汉关路笑尽英雄
辟长空 挽弓 啸入苍穹
谁留下 烽火连天照夜的勾划
又是谁在传说中寻他
千年后 挥兵破阵 不过一刹那
血雨腥风吻过了伤疤
楼烦城几场决胜 定襄破 长平封
汉关路笑尽英雄
梦归处 挽弓 啸入苍穹
万里沙 敌阵谁敢与我争高下
风云几度 惊半生戎马
拭铁甲 挥兵破阵 再望断天涯
血雨腥风吻过了伤疤
谁留下 烽火连天照夜 的勾划
又是谁在 传说中寻他
史册间 挥兵破阵 不过一刹那
血雨腥风吻过了伤疤
山河在 回首泪如雨下
*/