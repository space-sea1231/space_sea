#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n, top;
struct stak{
	int w, maxn;
}e[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	for (int i=1; i<=n; i++){
		int opt;
		cin >> opt;
		if (opt==0){
			int x;
			cin >> x;
			e[++top].w=x;
			e[top].maxn=max(e[top-1].maxn, x);
		}
		if (opt==1){
			top--;
		}
		if (opt==2){
			printf("%d\n", e[top].maxn);
		}
	}

	return 0;
}