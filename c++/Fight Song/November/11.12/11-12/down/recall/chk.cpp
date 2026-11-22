#include<stdio.h>
int n,p[0x66ccff];
int ABS(int x){return x<0?-x:x;}
bool chk(int n,int *p){
	for(int i=1;i<n;++i)if(!((p[i]^p[i+1])>ABS(p[i]-p[i+1])))return false;
	return true;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&p[i]);
	puts(chk(n,p)?"Is a solution":"Not a solution");
	return 0;
}
