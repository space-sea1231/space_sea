#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e5+10;
const int K=26;

int n;
int cnt[N][K];
string a, b;

signed main(){
	freopen("typer.in", "r", stdin);
	freopen("typer.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> a >> b >> n;
	int lena=a.size();
	a=" "+a;
	for (int i=1; i<=lena; i++){
		for (int j=0; j<K; j++){
			cnt[i][j]=cnt[i-1][j];
		}
		cnt[i][a[i]-'a']++;
	}
	if (b.size()==1){
		for (int i=1; i<=n; i++){
			int l, r;
			cin >> l >> r;
			if (cnt[r][b[0]-'a']-cnt[l-1][b[0]-'a']>0){
				printf("%d\n", r-l);
			}
			else{
				printf("%d\n", r-l+1);
			}
		}
		return 0;
	}
	for (int i=1; i<=n; i++){
		int l, r;
		cin >> l >> r;
		if (cnt[r][b[0]-'a']-cnt[l-1][b[0]-'a']>0&&cnt[r][b[1]-'a']-cnt[l-1][b[1]-'a']>0){
			printf("%d\n", r-l-1);
		}
		if (cnt[r][b[0]-'a']-cnt[l-1][b[0]-'a']>0&&cnt[r][b[1]-'a']-cnt[l-1][b[1]-'a']==0){
			printf("%d\n", r-l);
		}
		if (cnt[r][b[0]-'a']-cnt[l-1][b[0]-'a']==0&&cnt[r][b[1]-'a']-cnt[l-1][b[1]-'a']>0){
			printf("%d\n", r-l);
		}
		if (cnt[r][b[0]-'a']-cnt[l-1][b[0]-'a']==0&&cnt[r][b[1]-'a']-cnt[l-1][b[1]-'a']==0){
			printf("%d\n", r-l+1);
		}
	}
	return 0;
}