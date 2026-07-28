#include <bits/stdc++.h>
using namespace std;
const int Mod=998244353;
int t, n;
string s;
int main(){
	freopen("dog.in", "r", stdin);
	freopen("dog.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> t;
	while (t--){
		cin >> s;
		n=s.size();
		printf("%d\n", n);
	}
	return 0;
}