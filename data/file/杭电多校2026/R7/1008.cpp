#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
using namespace std;
int rd() {int x=0,f=1;char c=getchar();while(!isdigit(c))f=c=='-'?-1:f,c=getchar();while(isdigit(c))x=x*10+(c^48),c=getchar();return x*f;}

signed main() {
    int T=rd();
    while(T--) {
        puts("Yes");
        int n=rd(),x=rd();
        string S;
        cin>>S;
        printf("%d ",x);
        rep(i,0,n-2) {
            if(S[i]=='&') printf("%d ",x);
            else while(++i<n) printf("%d ",0);
        }
        puts("");
    }
    return 0;
}