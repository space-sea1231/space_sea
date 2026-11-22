#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int inf=1e8;

int n,m;
int a[100005];
int val[100005],len;

static inline bool check(int mid){
    queue<int>q;
    for(int i=1;i<=n;++i)
        if(a[i]==-1)
            q.push(1);
        else if(a[i]>=mid)
            q.push(0);
        else
            q.push(inf);
    while(q.size()>=3){
        int x=q.front();q.pop();
        int y=q.front();q.pop();
        int z=q.front();q.pop();
        q.push(min(x+y+z-max(max(x,y),z),inf));
    }
    return val+len+1-lower_bound(val+1,val+len+1,mid)>=q.front();
}

signed main(){
    freopen("mushroom.in","r",stdin);
    freopen("mushroom.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        a[i]=-1;
    for(int i=1;i<=m;++i){
        int x,w;
        cin>>w>>x;
        a[x]=w;
    }
    for(int i=1;i<=n-m;++i)
        cin>>val[++len];
    sort(val+1,val+len+1);
    int l=1,r=1e9,ret=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ret=mid;
            l=mid+1;
        }else
            r=mid-1;
    }
    cout<<ret<<endl;
    return 0;
}