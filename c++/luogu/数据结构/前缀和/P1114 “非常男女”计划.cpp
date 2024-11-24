#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, ans, sum;
int place[N<<1], a[N];
bool vis[N<<1];
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	vis[n]=1;
	for (int i=1; i<=n; i++){
		cin >> a[i];
		if (a[i]==0){
			a[i]=-1;
		}
		sum+=a[i];
		if (vis[sum+n]==0){
			vis[sum+n]=1;
			place[sum+n]=i;
		}else{
			ans=max(ans, i-place[sum+n]);
		}
	}
	printf("%d", ans);

	return 0;
}