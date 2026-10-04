#include<bits/stdc++.h>
using namespace std;
#define N 1000004
long long n,k,c[N],cnt;int a[N],mx;
int main(int argc,char **argv){
	if(argc!=3){cout<<"Usage: ./checker nanjing.in nanjing.out (Linux) | checker nanjing.in nanjing.out (Windows)"<<endl;return 4;}
	FILE *in=fopen(argv[1],"r");
	if(in==nullptr){cout<<"Failed to open "<<argv[1]<<endl;return 1;}
	FILE *out=fopen(argv[2],"r");
	if(out==nullptr){cout<<"Failed to open "<<argv[2]<<endl;return 2;}
	if(fscanf(in,"%lld%lld",&n,&k)!=2)return cout<<"Input format incorrect"<<endl,fclose(in),fclose(out),3;
	if(!(1<=n&&n<=250000))return cout<<"Input does not satisfy 1<=n&&n<=250000"<<endl,5;
	if(!(k>=0&&k<=n*(n-1)/2))return cout<<"Input does not satisfy 0<=k<=n*(n-1)/2"<<endl,5;
	fclose(in);
	mx=0;
	for(int i=1;i<=4*n;++i)c[i]=0;
	for(int i=1;i<=n;++i){
		if(fscanf(out,"%d",&a[i])!=1)return cout<<"Output format incorrect"<<endl,fclose(out),3;
	}
	for(int i=1;i<=n;++i){
		if(!(1<=a[i]&&a[i]<=4*n))return cout<<"a_i not in range [1,4*n]"<<endl,fclose(out),0;
	}
	for(int i=1;i<=n;++i){
		mx=max(mx,a[i]),++c[a[i]];
	}
	fclose(out);
	cnt=0;
	for(int i=1;i<=4*n;++i)cnt+=c[i]*(c[i]-1)/2;
	for(int q=2;q<=4*n;++q)for(int i=1,j=q;j<=4*n;++i,j+=q)cnt+=c[i]*c[j];
	if(cnt!=k)return cout<<"Wrong Answer."<<endl,0;
	if(mx<=2*n-1)return cout<<"Accepted."<<endl,0;
	if(mx<=3*n)return cout<<"Partial Score: 50%."<<endl,0;
	cout<<"Partial Score: 25%."<<endl;
	return 0;
}
