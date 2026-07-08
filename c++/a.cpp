#include <bits/stdc++.h>
using namespace std;
int p[5000010],mu[5000010],cnt,n,T;
bool isp[5000010];
long long phi[5000010];
unordered_map<int,int> summu;
unordered_map<int,long long> sumphi;
void euler_sieve(){
	isp[0]=isp[1]=true;
	mu[1]=phi[1]=1;
	for(int i=2;i<=5000000;++i){
		if(!isp[i]){
			p[++cnt]=i;
			mu[i]=-1;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&p[j]*i<=5000000;++j){
			isp[i*p[j]]=true;
			if(i%p[j]){
				mu[i*p[j]]=-mu[i];
				phi[i*p[j]]=phi[i]*phi[p[j]];
			}
			else{
				mu[i*p[j]]=0;
				phi[i*p[j]]=phi[i]*p[j];
                break;
			}
		}
	}
	for(int i=1;i<=5000000;++i){
		mu[i]+=mu[i-1];
		phi[i]+=phi[i-1];
	}
}
long long solve_mu(int x){
	if(x<=5000000) return mu[x];
	if(summu[x]) return summu[x];
	long long ans=1;
	for(register long long i=2,j;i<=x;i=j+1){
		j=x/(x/i);
		ans-=(j-i+1)*solve_mu(x/i);
	}
	return summu[x]=ans;
}
long long solve_phi(long long x){
	if(x<=5000000) return phi[x];
	if(sumphi[x]) return sumphi[x];
	long long ans=x*(x+1)/2;
	for(register long long i=2,j;i<=x;i=j+1){
		j=x/(x/i);
		ans-=(j-i+1)*solve_phi(x/i);
	}
	return sumphi[x]=ans;
}
int main(){
	euler_sieve();
	scanf("%d",&T);
	for(int i=1;i<=T;++i){
		scanf("%d",&n);
		printf("%lld %lld\n",solve_phi(n),solve_mu(n));
	}
	return 0;
}
