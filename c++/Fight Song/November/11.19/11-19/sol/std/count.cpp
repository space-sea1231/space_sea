#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1e7 + 10, mod = 998244353;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int T, n, m, k;
int f[N], inv[N];
inline int qpow(int a, int b){
	int ans = 1;
	while(b){
		if(b & 1)
		  ans = 1ll * ans * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return ans;
}
inline void init(){
	f[0] = f[1] = 1;
	for(int i = 2; i < N; ++i)
	  f[i] = 1ll * f[i - 1] * i % mod;
	inv[N - 1] = qpow(f[N - 1], mod - 2);
	for(int i = N - 2; i >= 0; --i)
	  inv[i] = 1ll * (i + 1) * inv[i + 1] % mod;
}
inline int binom(int n, int m){
	if(n < m)
	  return 0;
	if(!m || m == n)
	  return 1;
	return 1ll * f[n] * inv[m] % mod * inv[n - m] % mod;
}
inline void solve(){
	n = read(), m = read(), k = read();
	if(k & 1)
	  write(2ll * binom(m - 1, (k - 1) >> 1) % mod * binom(n - 1, (k - 1) >> 1) % mod);
	else
	  write((1ll * binom(m - 1, k >> 1) * binom(n - 1, (k >> 1) - 1) % mod + 1ll * binom(m - 1, (k >> 1) - 1) * binom(n - 1, k >> 1) % mod) % mod);
	putchar('\n');
}
bool End;
int main(){
    freopen("count.in","r",stdin);
    freopen("count.out","w",stdout);
	init();
	T = read();
	while(T--)
	  solve();
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}