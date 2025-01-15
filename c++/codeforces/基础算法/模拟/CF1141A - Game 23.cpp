#include <bits/stdc++.h>
using namespace std;
int a, b, c;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> a >> b;
	c=b/a;
	if (ceil(1.0*b/a)!=c){
		printf("-1");
		return 0;
	}
	int cnt=0;
	while(c%3==0){
		cnt++;
		c/=3;
	}
	while(c%2==0){
		cnt++;
		c/=2;
	}
	if (c!=1){
		printf("-1");
	}else{
		printf("%d", cnt);
	}
	return 0;
}