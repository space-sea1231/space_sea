#include<bits/stdc++.h>
#define FAST true
#define FIO true
#define DEBUG false
using namespace std;
#if FIO
void fio(string s,int i=0){
    freopen(((s+(i?to_string(i):""))+".in").c_str(),"r",stdin);
    freopen(((s+(i?to_string(i):""))+".out").c_str(),"w",stdout);
}
#endif
#define int long long
//#define int unsigned int
//#define int __int128
#define pii pair<int,int>
#define pi4 pair<pii,pii>
#define pi4v pair<pi4,vector<int>>
#if DEBUG
bool Memory_start;
void debug();
#endif
#if FAST
inline int read(){
    char c=getchar();
    int ret=0,f=1;
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        ret=(ret<<3)+(ret<<1)+c-'0';
        c=getchar();
    }return ret*f;
}
inline void write(int x,int op=0){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10,0);
    putchar((char)(x%10+'0'));
    if(op){
        if(op>0)puts("");
        if(op<0)putchar(' ');
        if(op==0)puts("114514");
    }
}
#endif
const int N=20,mod=998442353,inf=0x7f7f7f7f7f7f7f7f;
int T;
int n,m;
int mn=inf,ans;
struct dian{
    int w[N];
}a[N];
priority_queue<pi4v,vector<pi4v>,greater<pi4v>>q;
int dis[N][N];
bool vis[N];
map<int,int>mp;
int cnt=1;
int jc(int n){
    if(cnt>n)return mp[n];
    for(;cnt<=n;cnt++)mp[cnt]=mp[cnt-1]*cnt%mod;
    return mp[n]%mod;
}
int qpow(int x,int y){
    int ret=1;
    while(y){
        if(y&1)ret=ret*x%mod;
        x=x*x%mod;
        y>>=1;
    }return ret%mod;
}
void dij(int st){
    memset(dis,0x7f,sizeof dis);
    memset(vis,0,sizeof vis);
    vector<int>temp;
    temp.push_back(st);
    q.push({{{0,1},{1,st}},temp});
    dis[st][1]=0;
    while(!q.empty()){
        int nw=q.top().first.second.second,ds=q.top().first.first.second,fa=q.top().first.second.first;
        temp=q.top().second;
        q.pop();
        if(ds==n){
            if(dis[nw][ds]<mn){
                mn=dis[nw][ds];
                ans=fa;
            } else if(dis[nw][ds]==mn)(ans+=fa)%=mod;
            continue;
        }
        int w=0,tmp=1;
        for(int i=1;i<=n;i++){
            if(i==nw)continue;
            if(lower_bound(temp.begin(),temp.end(),i)!=temp.end()&&temp[lower_bound(temp.begin(),temp.end(),i)-temp.end()]==i)continue;
            int w=0,tmp=1;
            for(int j=1;j<=m;j++){
                int t=abs(a[i].w[j]-a[nw].w[j]);
                w+=t;
                tmp=tmp*qpow(jc(t),mod-2)%mod;
            }
            if(dis[i][ds+1]>dis[nw][ds]+w){
                dis[i][ds+1]=dis[nw][ds]+w;
                temp.push_back(i);
                q.push({{{dis[i][ds+1],ds+1},{fa*jc(w)%mod*tmp%mod,i}},temp});
                temp.pop_back();
            }
        }
    }
}
signed main(){
    fio("ge");
    T=read();
    mp[0]=1;
    while(T--){
        mn=inf,ans=0;
        m=read(),n=read();
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i].w[j]=read();
        for(int i=1;i<=n;i++){
            bool f=read();
            if(!f)continue;
            dij(i);
        }write(mn,-1),write(ans,1);
    }
#if DEBUG
    debug();
#endif
    return 0;
}
#if DEBUG
bool Memory_end;
void debug(){
    cerr<<"Time: "<<clock()<<" ms\n";
    cerr<<fixed<<setprecision(6)<<"Memory: "<<abs(&Memory_start-&Memory_end)/1024.0/1024.0<<" MB";
}
#endif