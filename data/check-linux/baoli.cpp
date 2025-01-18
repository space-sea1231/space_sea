#include<bits/stdc++.h>
#define il inline
#define ri register int
#define ll long long
#define lowbit(x) x&(-x)
using namespace std;
const int mod=9999991;
const int maxn =2e5+5;
const int maxx =1e6;
int x,n,m;
int st[maxn][20],lg[maxn],last[(maxx<<1)+5],f[maxn];
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
		f[i]=max(f[i-1],last[maxx+x]+1);
		st[i][0]=i-f[i]+1;
		last[x+maxx]=i;
	}
	init();
	while(m--){
		int L,R;
		scanf("%d%d",&L,&R);
		L++;R++;
		int pos=lower_bound(f+1+L,f+1+R,L)-f-1;
		//cout<<"pos="<<pos<<endl;
		printf("%d\n",max(pos-L+1,askmax(pos+1,R)));
	}
     return 0;
}

