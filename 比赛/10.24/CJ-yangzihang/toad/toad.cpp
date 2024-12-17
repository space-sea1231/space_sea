#include <bits/stdc++.h>
using namespace std;
const int N=5e2+10;
const int Mod=998244353;
int tot[N], n, cnt, top, num, ans[51]={0, 1, 4, 10, 37, 121, 451, 1639, 6259, 23923, 93502, 367852, 1465003};
char c[N], sum[N], a[7]={' ', '{', '[', '(', ')', ']', '}'};
void check(){
	top=0;
	for (int i=1; i<=n; i++){
		if (c[i]==' '){
			continue;
		}
		if (c[i]=='{'||c[i]=='['||c[i]=='('){
			sum[++top]=c[i];
		}else{
			if (c[i]=='}'&&sum[top]!='{'||c[i]==']'&&sum[top]!='['||c[i]==')'&&sum[top]!='('){
				return ;
			}
			top--;
		}
	}
	if (top){
		return ;
	}
	// for (int i=1; i<=n; i++){
	// 	printf("%c", c[i]);
	// }
	// printf("   ");
	// for (int i=1; i<=n; i++){
	// 	printf("%c", sum[i]);
	// }
	// printf("\n");
	num=(num+1)%Mod;
}
void serch(int dep){
	if (dep==cnt+1){
		check();
		return;
	}
	for (int i=0; i<7; i++){
		c[tot[dep]]=a[i];
		serch(dep+1);
	}
}
int main(){
    freopen("toad.in", "r", stdin);
    freopen("toad.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; i++){
		cin >> c[i];
		if (c[i]=='?'){
			tot[++cnt]=i;
		}
	}
	serch(1);
	printf("%d", num);

	return 0;
}