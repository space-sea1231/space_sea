#include <bits/stdc++.h>
#define int long long
using namespace std;
int a, b, p;
__int128 sum;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> a >> b >> p;
	a%=p, b%=p;
	sum=(__int128)a*b%p;
	cout << (int)sum;

	return 0;
}