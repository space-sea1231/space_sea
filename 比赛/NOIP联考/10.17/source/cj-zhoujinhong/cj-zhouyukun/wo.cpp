#include<bits/stdc++.h>
using namespace std;
#define DEBUG false
inline int read(){
	int v=0,f=1;
	char x=getchar();
	while(!(x>='0'&&x<='9')){if(x=='-') f=-f;x=getchar();}
	while(x>='0'&&x<='9'){v=v*10+(x-'0');x=getchar();}
	return v*f;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar(char(x%10+'0'));
}
bool st;
const int mod=998244353;
int Arr[2000100],t,n;
long long power(long long a,int b){
	long long Ans=1;
	while(b){
		if(b&1) Ans=Ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return Ans%mod;
}
bool ed;
int main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	t=read();
	while(t--){
		n=read();
		long long Cnt1=n,Cnt2=n,Cnt1_1=0,Cnt1_2=0,Cnt2_1=0,Cnt2_2=0;
		for(int i=1;i<=2*n;i++){
			Arr[i]=read();
			if(Arr[i]!=0){
				if(Arr[i]<=n){
					--Cnt1;
//					if(Arr[i]%2==1) ++Cnt1_1;
//					else ++Cnt1_2;
				}
				else{
					--Cnt2;
//					if(Arr[i]%2==1) ++Cnt2_1;
//					else ++Cnt2_2;
				}
			}
		}
		long long inv=power(2,mod-2);
		long long Ans=1;
		for(int i=1;i<=n;i++){
			int q=2*i-1,h=2*i;
			if(Arr[q]==0&&Arr[h]==0){
				if(Cnt1&&Cnt2){
					Ans=(Ans*Cnt1%mod*Cnt2%mod*2%mod)%mod;
					--Cnt1;
					--Cnt2;
				}else if(Cnt1){
					Ans=(Ans*(Cnt1==2?Cnt1:Cnt1-2)%mod*inv%mod*((Cnt1<=3?Cnt1-1:Cnt1-3)*inv%mod)%mod%mod)%mod;
					--Cnt1;
					--Cnt1;
				}else if(Cnt2){
					Ans=(Ans*(Cnt2==2?Cnt2:Cnt2-2)%mod*inv%mod*((Cnt2<=3?Cnt2-1:Cnt2-3)*inv%mod)%mod%mod)%mod;
					--Cnt2;
					--Cnt2;
				}
			}else if(Arr[q]==0){
				if(Arr[h]<=n){
					if(Cnt2){
						Ans=(Ans*Cnt2%mod)%mod;
						--Cnt2;
					}else{
						Ans=(Ans*(Cnt1*inv%mod)%mod)%mod;
						--Cnt1;
					}
				}else{
					if(Cnt1){
						Ans=(Ans*Cnt1%mod)%mod;
						--Cnt1;
					}else{
						Ans=(Ans*(Cnt2*inv%mod)%mod)%mod;
						--Cnt2;
					}
				}
			}else if(Arr[h]==0){
				if(Arr[q]<=n){
					if(Cnt2){
						Ans=(Ans*Cnt2%mod)%mod;
						--Cnt2;
					}else{
						Ans=(Ans*(Cnt1*inv%mod)%mod)%mod;
						--Cnt1;
					}
				}else{
					if(Cnt1){
						Ans=(Ans*Cnt1%mod)%mod;
						--Cnt1;
					}else{
						Ans=(Ans*(Cnt2*inv%mod)%mod)%mod;
						--Cnt2;
					}
				}
			}
//			cout<<Cnt1<<" "<<Cnt2<<" "<<Ans<<"\n";
		}
		write(Ans),putchar('\n');
	}
	#if DEBUG
	cerr<<abs(&st-&ed)/1024.00/1024.00<<" MB";
	#endif
	return min(0,0xde);
}
