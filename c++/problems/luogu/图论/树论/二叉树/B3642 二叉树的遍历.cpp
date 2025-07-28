#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int l[N], r[N];
int n;
void serch_1(int now){
	if (now==0){
		return ;
	}
	printf("%d ", now);
	serch_1(l[now]);
	serch_1(r[now]);
}
void serch_2(int now){
	if (now==0){
		return ;
	}
	serch_2(l[now]);
	printf("%d ", now);
	serch_2(r[now]);
}
void serch_3(int now){
	if (now==0){
		return ;
	}
	serch_3(l[now]);
	serch_3(r[now]);
	printf("%d ", now);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; i++){
		cin >> l[i] >> r[i];
	}
	serch_1(1);
	printf("\n");
	serch_2(1);
	printf("\n");
	serch_3(1);

	return 0;
}