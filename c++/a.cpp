#include<bits/stdc++.h>
#ifndef __linux__
#define gc getchar
#define pc putchar
#else
#define gc getchar_unlocked
#define pc putchar_unlocked
#endif
#define ll long long
#define i128 __int128
#define ull unsigned long long
#define ui unsigned int
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pull pair<ull,ull>
#define db double
#define ld long double
#define fi first
#define se second
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=a;i>=b;--i)
#define debug(x) cerr<<#x<<'='<<x<<'\n'
using namespace std;
namespace IO{
    template<typename T>
    inline void read(T &x){
        x=0;bool f=1;
        char c=gc();
        while(c<'0'||c>'9'){if(c=='-')f=0;c=gc();}
        while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=gc();
        x=f?x:-x;
    }
    template<typename T>
    void write(T x){
        if(x<0) pc('-'),x=-x;
        if(x>9) write(x/10);
        pc(x%10+'0');
    }
    inline void read(char &x){while(isspace(x=gc()));}
    inline void read(string &x){
        x.clear();
        char c=gc();
        while(isspace(c)&&c!=EOF) c=gc();
        while(!isspace(c)&&c!=EOF) x.push_back(c),c=gc();
    }
    inline void write(char x){pc(x);}
    inline void write(string x){for(auto c:x) pc(c);}
};using namespace IO;
const int N=2e5+5;
int n;
int to[N],deg[N],Deg[N],dp[N];
bool r[N],vis[N];
ll ans;
vector<int>ord;
signed main(){
    read(n);
    rep(i,1,n) read(to[i]),++deg[to[i]],r[i]=1,++Deg[to[i]];
    queue<int>q;
    rep(i,1,n) if(!deg[i]) q.push(i),r[i]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        ord.push_back(u),--deg[to[u]];
        if(!deg[to[u]]) q.push(to[u]),r[to[u]]=0;
    }
    reverse(ord.begin(),ord.end());
    rep(i,1,n){
        if(r[i]&&!vis[i]){
            int u=i,rsz=0;
            vector<int>ring;
            while(!vis[u]) vis[u]=1,ring.push_back(u),u=to[u],++rsz;
            for(int x:ring) dp[x]=rsz;
        }
    }
    for(int u:ord) dp[u]=dp[to[u]]+1;
    rep(i,1,n) write(dp[i]),pc('\n');
    return 0;
}