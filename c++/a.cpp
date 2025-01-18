#include<bits/stdc++.h>
#define il inline
#define ri register int
#define ll long long
#define lowbit(x) x&(-x)
using namespace std;
const int mod=9999991;
const int maxn =2e5+5;
const int M =1e6;
int x,n,m;
int st[maxn][20],lg[maxn],last[(M<<1)+5],pre[maxn];
void init(){
	lg[0]=-1;
	for(ri i=1;i<=n;i++)
	lg[i]=lg[i>>1]+1;
	for(ri j=1;(1<<j)<=n;j++)
	for(ri i=1;i+(1<<j)-1<=n;i++)
	st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
	
}

int askmax(int L,int R){
	if(L>R)return 0;
	int k=lg[R-L+1];
	return max(st[L][k],st[R-(1<<k)+1][k]);
	
}
int main(){
	//int n,m;
	scanf("%d%d",&n,&m);
	for(ri i=1;i<=n;i++){
		scanf("%d",&x);
		pre[i]=max(pre[i-1],last[M+x]+1);
		st[i][0]=i-pre[i]+1;
		last[x+M]=i;
	}
	init();
	while(m--){
		int L,R;
		scanf("%d%d",&L,&R);
		L++;R++;
		int mid=lower_bound(pre+1+L,pre+1+R,L)-pre-1;
		printf("%d\n",max(mid-L+1,askmax(mid+1,R)));
	}
     return 0;
}

