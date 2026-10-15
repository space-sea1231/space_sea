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
const int Mod = 1e9 + 7;

int n, m;
int a[N];
int C[N << 1][N << 1];

void Init() {
	C[0][0] = 1;
	for (int i = 1; i < (N << 1); i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = ((ll)C[i - 1][j - 1] + C[i - 1][j]) % Mod;
		}
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	Init();
	cin >> n >> m;
	int ans = 0;
	for (int i = 1; i <= m; i++) cin >> a[i];
	for (int i = 0; i < n; i++) {
		int mul = 1;
		for (int j = 1; j <= m; j++) {
			mul = (ll)mul * C[a[j] + n - i - 1][n - i - 1] % Mod;
		}
		ans = (ans + (ll)(i & 1 ? -1 : 1) * C[n][i] * mul % Mod + Mod) % Mod;
	}
	printf("%d\n", ans);
	return 0;
}		
/*
反乌托邦中的争夺　把愿望敲碎成粉末
心灵也被挂上门锁　看不清灯火
但我还想做些什么　其实还想要说很多
请你等等我　请你等等我
两块五的签字笔　东拼西凑的词句
妄想用它拯救你　顺便拯救我自己
只因为
你那渴望自由的心脏　困在一张没空隙的网
我们的周围并非没光亮　只是太耀眼将我们灼伤
在这个世界难免会迷茫　但别再把小刀带在身上
至少我还在为你而歌唱　在黑暗漫长的反乌托邦
即便我们都在这黑暗漫长的反乌托邦
忍着想要挣脱的生活　做出不想做的承诺
列车上坐错站的乘客　困惑着沉默
但我还想做些什么　其实还想要说很多
请你等等我　请你等等我
发着光的半平米　胡乱哼唱的旋律
但是还想拯救你　同时拯救我自己
就请你
放心大胆更妄为肆意　迈步向前别害怕失去
没有犯下任何错的你　在我心里只用做自己
这段胡乱拼凑的词语　如果伤到你也请你忘记
但若你又找不到意义　希望这首歌能被记起
活下去　活下去　活下去　活下去
在这反乌托邦里
*/