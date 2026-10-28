#include<stdio.h>
int main(){
	freopen("river.in","r",stdin);
	freopen("river.out","w",stdout);
	int n;
	scanf("%d",&n);
	if(n==2)return puts("-1"),0;
	if(n&1){for(int i=1;i<=n;++i)printf("%d%c",i,i==n?'\n':' ');}
	else{for(int i=2;i<=n;i+=2)printf("%d %d%c",i,i-1,i==n?'\n':' ');}
	return 0;
}
