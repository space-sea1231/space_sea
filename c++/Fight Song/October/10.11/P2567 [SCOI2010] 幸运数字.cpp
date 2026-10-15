#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;
typedef __int128_t i128;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e4 + 10;

ll a, b;
ll num[N];
ll ans;
int top;
bool vis[N];

void Dfs(int dep, ll cur) {
	if (dep > 10) return;
	Dfs(dep + 1, cur * 10 + 6);
	num[++top] = cur * 10 + 6;
	Dfs(dep + 1, cur * 10 + 8);
	num[++top] = cur * 10 + 8;
}
ll Calc(ll val) {
	ll l = (a + val - 1) / val, r = b / val;
	return r - l + 1;
}
void Dfs1(int dep, int cnt, ll val) {
	if (val > b) return;
	if (dep > top) {
		if (cnt == 0) return;
		ans += (cnt & 1 ? 1 : -1) * Calc(val);
		return;
	}
	Dfs1(dep + 1, cnt, val);
	int g = __gcd(num[dep], val);
	if ((i128)num[dep] / g * val <= b) Dfs1(dep + 1, cnt + 1, val / g * num[dep]);
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> a >> b;
	Dfs(1, 0);
	sort(num + 1, num + top + 1);
	// for (int i = 1; i <= top; i++) printf("%lld\n", num[i]);
	for (int i = 1; i <= top; i++) {
		for (int j = i + 1; j <= top; j++) {
			if (num[j] % num[i] == 0) vis[j] = true;
		}
	}
	int tmp = top; top = 0;
	for (int i = 1; i <= tmp; i++) {
		if (!vis[i]) num[++top] = num[i];
	}
	sort(num + 1, num + top + 1, [&](int a, int b){
		return a > b;
	});
	Dfs1(1, 0, 1);
	printf("%lld\n", ans);
	return 0;
}
/*
There's a girl but I let her get away
It's all my fault cause pride got in the way
And I'd be lying if I said I was ok
About that girl the one I let get away
I keep saying no
This can't be the way it was supposed to be
I keep saying no
There's gotta be a way to get you close to me
Now I know you gotta
Speak up if you want somebody
Can't let them get away, oh no
You don't wanna end up sorry
The way that I'm feeling everyday
(Don't you know)
No no no no
There's no home for the broken heart
No no no no
(Don't you know)
There's no home for the broken
There's a girl but I let her get away
It's my fault cause I said I needed space
I've been torturing myself night and day
About that girl, the one I let get away
I keep saying no
This can't be the way it was supposed to be
I keep saying no
There's gotta be a way to get you
Gotta be a way to get you close to me
You gotta
Speak up if you want somebody
Can't let them get away, oh no
You don't wanna end up sorry
The way that I'm feeling everyday
(Don't you know)
No no no no
There's no home for the broken heart
(Don't you know)
No no no no
There's no home for the broken
No home for me
No home cause I'm broken
No room to breathe
And I got no one to bla-ame
No home for me
No home cause I'm broken
About that girl
The one I let get away
So you better
Speak up if you want somebody
You can't let him get away oh no
You don't wanna end up sorry
The way that I'm feeling everyday
(Don't you know)
No no no no
There's no home for the broken heart
(Don't you know)
No no no no
There's no home for the broken
Oh
You don't wanna lose at love
It's only gonna hurt too much
I'm telling you
You don't wanna lose that love
It's only gonna hurt too much
I'm telling you
You don't wanna lose that love
Cause There's no home for the broken
About that girl
The one I let get away
*/