#include <iostream>
#include <stdio.h>

using namespace std;

const int N=1e5+10;

int n;
int sum;
int a[N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i=1; i<=n; i++){
		cin >> a[i];
		sum+=max(0, a[i]-a[i-1]);
	}
	printf("%d\n", sum);
	
	return 0;
}