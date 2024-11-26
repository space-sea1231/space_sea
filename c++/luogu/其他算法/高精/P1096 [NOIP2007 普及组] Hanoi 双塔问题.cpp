#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n, len, sum[N];
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
	cin >> n;
	sum[1]=2, len=1;
	int x=0, cnt;
	for (int i=2; i<=n; i++){
		for (int j=1; j<=len; j++){
			sum[j]*=2;
		}
		sum[1]+=2;
		for (int j=1; j<=len; j++){
			if (sum[j]>=10){
				sum[j]%=10;
				sum[j+1]++;
			}
		}
		if (sum[len+1]){
			len++;
		}
	}
	for (int i=len; i>=1; i--){
		printf("%d", sum[i]);
	}

	return 0;
}