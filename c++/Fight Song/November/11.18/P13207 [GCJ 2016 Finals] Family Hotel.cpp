#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e7 + 10;
const int Mod = 1e9 + 7;

int T;
int f[N];
int inv[N];

int Pow(int a, int b) {
	int sum = 1;
	while (b) {
		if (b & 1) sum = (ll)sum * a % Mod;
		a = (ll)a * a % Mod;
		b >>= 1;
	}
	return sum;
}
void Solve(int cur) {
	int n, m;
	cin >> n >> m;
	// cerr << f[m] << " " << f[n - m + 1] << "\n";
	printf("Case #%d: %d\n", cur, (1 - (ll)f[m] * f[n - m + 1] % Mod + Mod) % Mod);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	inv[1] = 1;
	for (int i = 2; i < N; i++) inv[i] = (ll)(Mod - (Mod / i)) * inv[Mod % i] % Mod;
	f[1] = 1, f[2] = 0;
	int sum = f[1];
	// cerr << inv[2] << " " << (ll)inv[2] * 2 % Mod << "\n";
	for (int i = 3; i < N; i++) {
		f[i] = (ll)inv[i - 1] * sum % Mod;
		sum = ((ll)sum + f[i - 1]) % Mod;
	}
	cin >> T;
	for (int _ = 1; _ <= T; _++) Solve(_);
	return 0;
}
/*
🌌 星空知识卡片 04：北极星（Polaris）

【📍 基础档案】

坐标：小熊座 α 星（勾陈一），距北天极仅 0.65°，是离“天球北极”最近的亮星。

距离：约 440 光年。

视星等：1.98 等（全天只排第 48 位，是个“靠位置出名”的二等星）。

光谱型：F7Ib（黄白色超巨星，表面温度约 6000 K）。

【📖 文科浪漫与神话】

中国人叫它“北辰”。《论语·为政》说：“为政以德，譬如北辰，居其所而众星共之。”
可它并不是永远的——受地球岁差影响（周期约 2.6 万年），
公元前 3000 年排在那个位置的是右枢，
公元 14000 年将轮到织女星。
它的“恒定”，只是人类恰好赶上的一段任期。

【🔭 硬核数据与物理】

三口之家：北极星 Aa 是黄超巨星，Ab 约 30 年绕它一圈，B 则远在 2400 AU 外。

会“呼吸”的星：它是一颗造父变星，每 3.97 天脉动一次。
亮度起伏小到肉眼难辨，却成了测量星系距离的“标准烛光”——相当于给宇宙量尺做校准的砝码。

【🧭 观测指南】

怎么找：从北斗的天璇到天枢连线，朝斗口外侧延长 5 倍；
晚秋北斗位置低，也可以用仙后座 W 的尖角朝开口方向指。

小提醒：它的高度角就等于当地纬度，长沙约 28°，得往正北低空找。
它几乎不动，是天然的星轨圆心：长曝光十几分钟，众星绕它画圈，它自己纹丝不动，大概这就是“众星共之”。

*/