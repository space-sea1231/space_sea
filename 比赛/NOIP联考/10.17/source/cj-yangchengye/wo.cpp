#include<bits/stdc++.h>
#define md 998244353
#define int long long
using namespace std;
inline char fgc(){
    static char buf[1<<17],*p=buf,*q=buf;
    return p==q&&(q=buf+fread(p=buf,1,1<<17,stdin),p==q)
    ?EOF:*p++;
}
inline int rint(){
    int x=0,s=fgc(),f=1;
    for(;s<'0'||'9'<s;s=fgc())f=s=='-'?-f:f;
    for(;'0'<=s&&s<='9';s=fgc())x=x*10+(s^'0');
    return x*f;
}
int p[2*1000000+1];
int js[7];
__int128 sum(int x,int a){
	int base=a;
	__int128 w=1;
	while(x){
		if(x%2==1){
			x--;
			w*=base;
			w%=md;
		}
		base*=base;
		base%=md;
		x/=2;
	}
	return w;
}
__int128 A(int n,int m){
	__int128 w=1;
	for(int i=n;i>=n-m+1;i--){
		w*=i;
		w%=md;
	}
	return w;
}
__int128 C(int n,int m){
	__int128 w1=1,w2=1;
	for(int i=1;i<=min(m,n-m);i++){
		w1*=(n-min(m,n-m)+i);
		w2*=(min(m,n-m)-i+1);
		__int128 w3=__gcd(w1,w2);
		w1/=w3;
		w2/=w3;
	}
	return (__int128)w1;
}
void out(__int128 x){
	if(x>=10){
		out(x/10);
	}
	putchar(x%10+'0');
}
int bj[2000001];
signed main(){
//	freopen("abab.in","r",stdin);
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	int T=rint();
	int n;
	__int128 ans=1;
	int sum1=n,sum2=n;
	while(T){
		n=rint();
		ans=1;
		sum1=n,sum2=n;
		T--;
		for(int i=1;i<=2*n;i++){
			bj[i]=0;
		}
		for(int i=1;i<=6;i++){
			js[i]=0;
		}
		for(int i=1;i<=2*n;i++){
			p[i]=rint();
			if(p[i]<=n&&p[i]!=0){
				sum1--;
			}
			else if(p[i]>n){
				sum2--;
			}
			if(i%2==0){
				if(p[i]<p[i-1]){
					swap(p[i],p[i-1]);
				}
				if(p[i]==0&&p[i-1]==0){
					js[1]++;
				}
				else if(p[i]<=n&&p[i]!=0&&p[i-1]==0){
					js[2]++;
					bj[p[i]]=1;
				}
				else if(p[i]>n&&p[i-1]==0){
					js[3]++;
					bj[p[i]]=1;
				}
				else if(p[i]<=n&&p[i-1]<=n&&p[i-1]!=0){
					bj[p[i]]=1;
					bj[p[i-1]]=2;
					js[4]++;
				}
				else if(p[i]>n&&p[i-1]>n){
					bj[p[i]]=1;
					bj[p[i-1]]=2;
					js[5]++;
				}
				else if(p[i]>n&&p[i-1]<=n){
					js[6]++;
				}
			}
		}
//		for(int i=1;i<=6;i++){
//			cout<<js[i]<<' ';
//		}
//		cout<<'\n';
//		cout<<sum1<<' '<<sum2<<'\n';
		if(js[4]>js[5]){
			int qwq=js[4]-js[5],qaq=0,ToT=0;
			for(int i=1;ToT<=qwq;i++){
				if(bj[i+n]==1){
					qaq++;
				}
				if(bj[i+n]!=2){
					ToT++;
				}
			}
//			cout<<qwq<<' '<<qaq<<'\n';
			ans*=A(sum2,qaq);
//			out(ans);
//			puts("");
			sum2-=qaq;
			ans%=md;
			ans*=A(sum2,qwq-qaq);
//			out(ans);
//			puts("");
			sum2-=(qwq-qaq)*2;
			ans%=md;
			ans*=C(js[1],qwq-qaq);
			js[1]-=(qwq-qaq);
//			out(ans);
//			puts("");
			ans%=md;
			js[5]=js[4];
			ans*=A(sum1,sum1);
//			out(ans);
//			sum1=0;
			ans%=md;
			ans*=sum(js[1],2);
//			out(ans);
//			puts("");
			ans%=md;
			ans*=A(sum2,sum2);
//			out(ans);
//			puts("");
			sum2=0;
			ans%=md;
		}
		else if(js[5]>js[4]){
			int qwq=js[5]-js[4],qaq=0,ToT=0;
			for(int i=1;ToT<=qwq;i++){
				if(bj[i]==1){
					qaq++;
				}
				if(bj[i]!=2){
					ToT++;
				}
			}
//			cout<<qwq<<' '<<qaq<<'\n';
			ans*=A(sum1,qaq);
//			out(ans);
//			puts("");
			sum1-=qaq;
			ans%=md;
			ans*=A(sum1,qwq-qaq);
//			out(ans);
//			puts("");
			sum1-=(qwq-qaq)*2;
			ans%=md;
			ans*=C(js[1],qwq-qaq);
			js[1]-=(qwq-qaq);
//			out(ans);
//			puts("");
			ans%=md;
			js[4]=js[5];
			ans*=A(sum1,sum1);
//			out(ans);
//			sum1=0;
			ans%=md;
			ans*=sum(js[1],2);
//			out(ans);
//			puts("");
			ans%=md;
			ans*=A(sum2,sum2);
//			out(ans);
//			puts("");
			sum2=0;
			ans%=md;
		}
		else{
			ans*=A(sum1,sum1);
			sum1=0;
			ans%=md;
			ans*=sum(js[1],2);
			ans%=md;
			ans*=A(sum2,sum2);
			sum2=0;
			ans%=md;
		}
		out(ans);
		puts("");
	}
	return 0;
}
/*
2
2
1 2 0 0
2
1 0 0 0
*/
