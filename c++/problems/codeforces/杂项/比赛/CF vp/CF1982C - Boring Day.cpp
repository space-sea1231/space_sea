#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
int t, n, l, r;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while (t--){
		int l_point=1, r_point=0, cnt=0, sum=0;
		cin >> n >> l >> r;
		for (int i=1; i<=n; i++){
			cin >> a[i];
		}
		while (l_point<=n&&r_point<=n){
			if (sum>=l&&sum<=r){
				cnt++;
				l_point=r_point+1;
				sum=0;
			}
			else if (sum<l){
				sum+=a[++r_point];
			}
			if (sum>r){
				sum-=a[l_point++];
			}
		}
		printf("%d\n", cnt);
	}

	return 0;
}