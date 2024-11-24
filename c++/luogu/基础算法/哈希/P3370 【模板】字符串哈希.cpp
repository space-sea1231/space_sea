#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int N=1e4+10;
const int M=1510;
const int base=131;
const int Mod_1=19260817;
const int Mod_2=19660813;
int vis_1[N], vis_2[N];
int n, cnt, sum;
bool flag;
char c[M];
int hash_1(string c){
	int len=c.size(), sum;
	for (int i=0; i<len; i++){
		sum=(sum*base+(int)c[i])%Mod_1;
	}
	return sum;
}
int hash_2(string c){
	int len=c.size(), sum;
	for (int i=0; i<len; i++){
		sum=(sum*base+(int)c[i])%Mod_2;
	}
	return sum;
}
signed main(){ 
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	int x, y;
	for (int i=1; i<=n; i++){
		cin >> c, flag=0;
		x=hash_1(c), y=hash_2(c);
		for (int j=1; j<=cnt; j++){
			if (vis_1[j]==x&&vis_2[j]==y){
				flag=1;
				break;
			}
		}
		if (!flag){
			vis_1[++cnt]=x, vis_2[cnt]=y;
			sum++;
		}
	}
	printf("%llu", sum);

	return 0;
}