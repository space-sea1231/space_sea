#include <bits/stdc++.h>
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

inline static int read(){
    int sum=0,neg=0,ch=getchar();
    while(!isdigit(ch)) neg|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) sum=sum*10+(ch^48),ch=getchar();
    return neg?-sum:sum;
}

int n,a[20],b[20];
signed main(){
    // freopen("wo2.in","r",stdin);
    // freopen("wo2.out","w",stdout);
    int T=read();
    while(T--){
        n=read(); int ans=0,cnt=0;
        for(int i=1;i<=2*n;i++) b[i]=read(),a[i]=i;
        do{
            int sum=0;
            for(int i=1;i<=2*n;i++) if(b[i]&&a[i]!=b[i]) goto Continue;
            for(int i=1;i<=n;i++) sum+=abs(a[2*i-1]-a[2*i]);
            if(ans<sum) ans=sum,cnt=0; cnt+=ans==sum;
            Continue:;
        }while(next_permutation(a+1,a+2*n+1));
        printf("%d\n",cnt);
    }
    return 0;
}
