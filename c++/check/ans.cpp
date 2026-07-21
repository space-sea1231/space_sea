#include<bits/stdc++.h>
#define int long long
using namespace std;
int fa[200010],f[200010],a[200010],b[200010];
int find(int x){
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
struct node{
    int x;
    bool friend operator<(node i,node j){
        return b[i.x]*a[j.x]>b[j.x]*a[i.x];
    }
};
priority_queue<node>q;

signed main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++)cin>>b[i];
        for(int i=1;i<=n;i++)cin>>f[i];
        for(int i=1;i<=n;i++)fa[i]=i;
        for(int i=2;i<=n;i++){
            q.push({i});
        }
        int sum=0;
        while(q.size()){
            node u=q.top();
            q.pop();
            if(u.x==1)continue;
            int Fa=find(f[u.x]);
            sum+=a[u.x]*b[Fa];
            fa[u.x]=Fa;
            a[Fa]+=a[u.x],b[Fa]+=b[u.x];
        }
        cout<<sum<<"\n";
        while(q.size())q.pop();
    }
    return 0;
}