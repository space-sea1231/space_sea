#include <bits/stdc++.h>
using namespace std;
const int N=4e5+10;
bool a[N];
int cnt, ans, n;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; i++){
		cin >> a[i];
		a[i+n]=a[i];
	}
	for (int i=1; i<=n*2; i++){
		if (a[i]){
			cnt++;
		}else{
			ans=max(ans, cnt);
			cnt=0;
		}
	}
	ans=max(ans, cnt);
	printf("%d", ans);
	
	return 0;
}