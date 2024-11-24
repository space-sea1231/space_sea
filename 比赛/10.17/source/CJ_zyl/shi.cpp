#include<bits/stdc++.h>
using namespace std;
const int N=1e6+3;
string s;
int n;
int pre[N],op[N];
void out(vector<int>&ans,int x){
    if(pre[x]==-1)return;
    out(ans,pre[x]);ans.push_back(op[x]);
}
void solve(){
    cin>>s;n=s.size();int st=0;
    for(int i=0;i<n;++i)if(s[i]=='1')st|=1<<i;
    for(int s=0;s<1<<n;++s)pre[s]=0;
    pre[st]=-1;queue<int>q;q.push(st);
    while(!q.empty()){
        int x=q.front();q.pop();
        for(int i=1;i<n-1;++i){
            int y=x;
            if(x&(1<<i))y&=((1<<n)-1)^(1<<i-1)^(1<<i+1);
            else y^=(1<<i-1)^(1<<i+1);
            if(!pre[y])pre[y]=x,op[y]=i,q.push(y);
        }
    }
    for(int k=n;~k;--k)
        for(int s=(1<<n)-1;~s;--s)if(__builtin_popcount(s)==k&&pre[s]){
            printf("%d\n",k);vector<int>ans;out(ans,s);
            printf("%lu\n",ans.size());
            for(auto x:ans)printf("%d ",x+1);puts("");
            return;
        }
}
int main(){
    int u,v,w,x,y,z;
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;for(cin>>T;T--;)solve();
    return 0;
}