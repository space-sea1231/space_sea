#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int Mod = 998244353;

int n, m;
int Pow(int a, int b) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = (ll)sum * a % Mod;
        a = (ll)a * a % Mod;
        b >>= 1;
    }
    return sum;
}
signed main() {
    freopen("detect.in", "r", stdin);
    freopen("detect.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    if (m < 3) {
        if (m == 1) printf("1\n1 %d\n", n);
        if (m == 2) printf("2\n1 %d\n1 %d\n", n, n);
    } else if (n - 1 < m / 3 + (m % 3 == 2)) { // 95618 305913
        int val = m / (n - 1);
        int a = m - val * (n - 1);
        // cerr<<val << " " << a << "\n";
        printf("%lld\n", (ll)Pow(val, n - 1 - a) * Pow(val + 1, a) % Mod);
        for (int i = 1; i <= n - 1 - a; i++) {
            for (int j = 1; j <= val; j++) {
                printf("%d %d\n", i, i + 1);
            }
        }
        for (int i = n - a; i < n; i++) {
            for (int j = 1; j <= val + 1; j++) {
                printf("%d %d\n", i, i + 1);
            }
        }
    } else {
        if (m % 3 == 1) {
            printf("%lld\n", (ll)Pow(3, m / 3 - 1) * 4 % Mod);
            for (int i = 1; i <= m / 3 - 1; i++) {
                for (int j = 1; j <= 3; j++) {
                    printf("%d %d\n", i, i + 1);
                }
            }
            for (int i = 1; i <= 4; i++) printf("%d %d\n", m / 3, n);
        }
        if (m % 3 == 2) {
            printf("%lld\n", (ll)Pow(3, m / 3) * 2 % Mod);
            for (int i = 1; i <= m / 3; i++) {
                for (int j = 1; j <= 3; j++) {
                    printf("%d %d\n", i, i + 1);
                }
            }
            for (int i = 1; i <= 2; i++) printf("%d %d\n", m / 3 + 1, n);
        }
        if (m % 3 == 0) {
            printf("%lld\n", (ll)Pow(3, m / 3));
            for (int i = 1; i <= m / 3 - 1; i++) {
                for (int j = 1; j <= 3; j++) {
                    printf("%d %d\n", i, i + 1);
                }
            }
            for (int i = 1; i <= 3; i++) printf("%d %d\n", m / 3, n);
        }
        
    }
    return 0;
}
/*
听雨落染东风 漾出江水溶溶
却不曾 拂去眉间霜浓
抬首向长空 伶仃孤鸿
描画几重 只影过云虹
历经四季枯荣 可笑往日懵懂
人间事 何曾亘古隽永
聚散亦万种 一如长风
来去匆匆 余生难相逢
折桥畔杨柳 宛转舞云袖
醉邀星斗 歌尽扇底桃花满楼
不见故人游 月下光影旧
红颜枯骨岁月中无声腐朽
忽忆少时旧梦 犹记昔年姿容
无羁行 醉卧林间芳丛
悲欢皆尘封 人世倥偬
难得情钟 此意何处穷
风吹雪满头 孤身空白首
画地自囚 打马而过恰逢豆蔻
再无人回眸 韶华终未留
岁岁相思只得诉予远山岫
望寒秋 碧空悠悠
唯见孤帆天际流
从别后 终归一无所有
折桥畔杨柳 宛转舞云袖
醉邀星斗 歌尽扇底桃花满楼
不见故人游 月下光影旧
红颜枯骨岁月中无声腐朽
风吹雪满头 孤身空白首
画地自囚 打马而过恰逢豆蔻
再无人回眸 韶华终未留
岁岁相思只得诉予远山岫
*/