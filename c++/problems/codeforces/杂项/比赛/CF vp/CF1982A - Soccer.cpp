#include <bits/stdc++.h>
using namespace std;
int t, x_first, y_first, x_second, y_second;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while (t--){
		cin >> x_first >> y_first >> x_second >> y_second;
		if (x_first<y_first&&x_second>y_second) printf("NO\n");
		else if (y_first<x_first&&y_second>x_second) printf("NO\n");
		else printf("YES\n");
	}

	return 0;
}