#include <bits/stdc++.h>
using namespace std;
int t, x, y, k, tmp;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while (t--){
		cin >> x >> y >> k;
		while (k&&x!=1){
			tmp=min(k, y-(x%y));
			k-=tmp;
			x+=tmp;
			while (x%y==0) x/=y;
		}
		k%=(y-1);
		x+=k;
		if (x%y==0) x/=y;
		printf("%d\n", x);
	}

	return 0;
}