#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e3 + 10;
const int M = 1e6 + 10;

int n, m;
int cnt;
int prime[M];
bool vis[M];

void Prime() {
    for (int i = 2; i < M; i++) {
        if (!vis[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] < M; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    Prime();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        if (l < 1 || r > m) printf("Crossing the line\n");
        else printf("%d\n", upper_bound(prime + 1, prime + cnt + 1, r) - lower_bound(prime + 1, prime + cnt + 1, l));
    }
    return 0;
}















/*
感受停在我发端的指尖
如何瞬间冻结时间
记住望着我坚定的双眼
也许已经没有明天
面对浩瀚的星海
我们微小得像尘埃
漂浮在一片无奈
缘分让我们相遇乱世以外
命运却要我们危难中相爱
也许未来遥远在光年之外
我愿守候未知里为你等待
我没想到 为了你我能疯狂到
山崩海啸 没有你根本不想逃
我的大脑 为了你已经疯狂到
脉搏心跳 没有你根本不重要
一双围在我胸口的臂弯
足够抵挡天旋地转
一种执迷不放手的倔强
足以点燃所有希望
宇宙磅礴而冷漠
我们的爱微小却闪烁
颠簸却如此忘我
缘分让我们相遇乱世以外
命运却要我们危难中相爱
也许未来遥远在光年之外
我愿守候未知里为你等待
我没想到 为了你我能疯狂到
山崩海啸 没有你根本不想逃
我的大脑 为了你已经疯狂到
脉搏心跳 没有你根本不重要
也许航道以外 是醒不来的梦
乱世以外 是纯粹的相拥
我没想到 为了你我能疯狂到
山崩海啸 没有你根本不想逃
我的大脑 为了你已经疯狂到
脉搏心跳 没有你根本不重要
相遇乱世以外 危难中相爱
相遇乱世以外 危难中相爱
我没想到 [2]

Brevity 简洁
soul 灵魂
*/