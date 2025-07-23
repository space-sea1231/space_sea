#include <bits/stdc++.h>
// #define int unsigned long long
using namespace std;
const int Mxdt=100000; 
inline char gc(){
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int t=0,f=0;char v=gc();
	while(v<'0')f|=(v=='-'),v=gc();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=gc();
	return f?-t:t;
}
const unsigned long long mod=18446744073709551616;
int n;
int a[1000005],b[1000005]; 
int tot;
int tot2;
int tian[1000005];
int ky[1000005];
int jie[1000005];
unsigned long long ans;
inline bool cmp(int x,int y){
    return x>y;
}
signed main(){
    n=read();
    for(int i=1;i<=n;++i){
        a[i]=read();
    }
    for(int i=1;i<=n;++i){
        b[i]=read();
    }
    sort(a+1,a+n+1); sort(b+1,b+n+1);
    ky[++tot]=a[n]+1; jie[tot]=1002000000;
    for(int i=n-1;i>=1;--i){
        if(a[i] < a[i+1]){
            if(a[i]<a[i+1]-1){
                ky[++tot]=a[i]+1;
                jie[tot]=a[i+1]-1;
            }
        }else{
            tian[++tot2]=ky[tot]-a[i];
            ky[tot]+=1;
            if(ky[tot]>jie[tot]) tot--;
        }
    }
    sort(tian+1,tian+tot2+1,cmp);
    for(int i=1;i<=tot2;++i){
        unsigned long long aa=1ull*b[i]*tian[i];
        ans=ans+aa;
        if(ans>mod)ans-=mod;
    }   
    cout<<ans<<'\n';
    return 0;
}