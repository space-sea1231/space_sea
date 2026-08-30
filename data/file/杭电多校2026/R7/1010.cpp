#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
using namespace std;
int rd() {int x=0,f=1;char c=getchar();while(!isdigit(c))f=c=='-'?-1:f,c=getchar();while(isdigit(c))x=x*10+(c^48),c=getchar();return x*f;}
const int N=100005,mod=998244353;
void add(int &x,int y) {x+=y,x-=x>=mod?mod:0;}
int n,a[N],s[N],dp[N];
char S[N];
bool check() {
    rep(i,2,n) if(S[i]==S[i-1]) return 0;
    return 1;
}
int Main() {
    scanf("%s",S+1);
    n=strlen(S+1);
    if(check()) return 1;
    unordered_map<int,vector<int>> pos;
    rep(i,1,n) a[i]=(S[i]=='0'?-1:1),s[i]=s[i-1]+a[i],pos[s[i]].push_back(i);
    rep(i,0,n) dp[i]=0;
    dp[0]=1;
    int ans=0;
    rep(i,1,n) {
        add(dp[i],dp[i-1]);
        vector<int>& vec=pos[s[i-1]-a[i]];
        auto it=lower_bound(vec.begin(),vec.end(),i+1);
        if(it!=vec.end()) add(dp[*it],dp[i-1]);
        if(s[i]==s[n]) add(ans,dp[i]);
    }
    return ans;
}
signed main() {
    int T=rd();
    while(T--) printf("%d\n",Main());
    return 0;
}