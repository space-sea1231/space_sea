#include <bits/stdc++.h>
using namespace std;
int n, sum, ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	while (sum+5<=n){
		sum+=5;
		if ((n-sum)%3==0){
			ans=sum;
		}
	}
	if (ans==0&&n%3){
		printf("-1");
	}else{
		printf("%d", ans/5+(n-ans)/3);
	}

	return 0;
}