#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e6 + 10;
const int K = 31;

int n;
int a[N], b[N], c[K];
int lst[N], mn[K];
int cnt[K][N];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < K; i++) b[i] = INF;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < K; j++) {
			if (!(a[i] & (1 << j))) {
				b[j] = min(b[j], a[i]);
				break;
			}
		}
	}
	ull ans = 0;
	for (int i = 0; i < K; i++) cnt[i][0] = b[i] + 1;
	for (int i = 1; i <= n; i++) {
		if (a[i] < n) {
			for (int j = 0; j < K; j++) if (a[i] <= b[j]) cnt[j][lst[a[i]]]--, cnt[j][i]++;
			lst[a[i]] = i;
		}
		for (int j = 0; j < K; j++) while (!cnt[j][mn[j]]) mn[j]++;
		for (int j = 0; j < K; j++) if (a[i] & (1 << j)) c[j] = i;
		for (int j = 0; j < K; j++) {
			if (n <= b[j]) ans += (1ull << j) * c[j];
			else ans += (1ull << j) * max(c[j], mn[j]);
		}
	}
	printf("%llu\n", ans);
	return 0;
}
/*
森林很美是我的家 无忧无虑嘻嘻哈哈
可我心里还有个梦啊 想去海角 想去天涯
有谁和我一起出发 看看世界到底多大
他们笑我是个小呆瓜 我不放弃 也不害怕
抓住它 时光的尾巴 别笑话 天真的想法
风很大 也会想家 梦的旅途会到达
Big hero says（大英雄说）
太阳花 绽放的脸颊 别牵挂 和星星说话
年轻的步伐 总会到达
总会到达 总会到达
*/