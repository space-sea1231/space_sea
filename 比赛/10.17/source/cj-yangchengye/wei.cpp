#include<bits/stdc++.h>
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
int a[400001];
int main(){
//	freopen("abab.in","r",stdin);
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	int T=rint();
	while(T){
		--T;
		int n=rint();
		for(int i=1;i<=n;i++){
			a[i]=rint();
		}
		long long ans=0;
		int js=0;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				long long w=0;
				swap(a[i],a[j]);
				for(int k=1;k<=n;k++){
					if(a[k]>a[k-1]){
						js++;
					}
					else{
						w+=(js+1)*(js)/2;
						js=0;
					}
				}
				w+=(js+1)*(js)/2;
				js=0;
				swap(a[i],a[j]);
				ans=max(ans,w);
			}
		}
		long long w=0;
//				swap(a[i],a[j]);
		for(int k=1;k<=n;k++){
			if(a[k]>a[k-1]){
				js++;
			}
			else{
				w+=(js+1)*(js)/2;
				js=0;
			}
		}
		w+=(js+1)*(js)/2;
		js=0;
//		swap(a[i],a[j]);
		ans=max(ans,w);
		printf("%lld\n",ans);
	}
	return 0;
}
