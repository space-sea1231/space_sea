#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define more_test 1
const int mod = 998244353;
const int N = 3e6 + 5;
int jc[N];
inline int ksm(int a , int b){
	int res = 1;
	while(b){
		if(b&1) (res *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return res;
}
inline int inv(int a){
	int b = mod - 2 , res = 1;
	while(b){
		if(b&1) (res *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return res;
}
inline int C(int n , int m){
	if(n < m) return 0;
	return jc[n] * inv(jc[m])  % mod/* * inv(jc[n - m]) % mod*/;
}
inline int read(){
	int f = 1 , s = 0;
	char c = getchar();
	while(c< '0' || c > '9'){
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		s = (s << 1) + (s << 3) + c - '0';
		c = getchar();
	}
	return f * s;
}
inline void print(int x){
	if(x>9)print(x/10);
	putchar(x%10 + '0');
}
inline void solve(){
	int n = read();
	vector<int> p(n * 2) , vis(n * 2 + 5) , is(n * 2 + 5);
	for(int i = 0;i < (n * 2);i++){
		p[i] = read();
	}
	int jyq = n + 1 , www = 0;
	for(int i = 0;i < (n * 2);i += 2){
		if(p[i] && p[i + 1]){
			www++;
			if(p[i] < p[i + 1]) swap(p[i] , p[i + 1]);
			is[p[i + 1]] = 1;
			is[p[i]] = 1;
		}
		if((p[i] != 0) ^ (p[i + 1] != 0)){
			if(p[i] != 0) swap(p[i] , p[i + 1]);
		}
	}
	// for(int i = 0;i < (n * 2);i++){
	// 	cout<<p[i]<<' ';
	// }
	// cout<<'\n';
	int dw = 2 * n;
	int jyq_not_ac = n - www;
	while(jyq_not_ac){
		if(!is[dw]){
			// cerr<<dw<<' ';
			vis[dw] = 1;
			dw--;
			jyq_not_ac--;
		}
		else{
			dw--;
		}
	}
	// cerr<<endl;
	for(int i = 0;i < (n * 2);i += 2){
		if((p[i] != 0) ^ (p[i + 1] != 0)){
			if(p[i]){
				if((!vis[p[i]])) swap(p[i] , p[i + 1]);
			}
			else{
				if((vis[p[i + 1]])) swap(p[i] , p[i + 1]);
			}
		}
	}
	// for(int i = 0;i < (n * 2);i++){
	// 	cout<<p[i]<<' ';
	// }
	// cout<<'\n';
	int c1 = 0 , c2 = 0 , cc = 0;
	for(int i = 0;i < (n * 2);i++){
		if(p[i]) continue;
		if(i % 2)c1++;
		else c2++;
	}
	int res = jc[c1] * jc[c2] % mod;
	// cerr<<res<<endl;
	for(int i = 0;i < (n * 2);i += 2){
		if(p[i] == 0 && p[i + 1] == 0) cc++;
	}
	(res *= ksm(2 , cc)) %= mod;
	print(res);
	putchar('\n');
}
signed main(){
	freopen("wo.in" , "r" , stdin);
	freopen("wo.out" , "w" , stdout);
	jc[0] = 1;
	for(int i = 1;i <= N - 5;i++){
		jc[i] = jc[i - 1] * i % mod;
	}
	int _ = 1;
	if(more_test) cin >> _;
	while(_--) solve();
}