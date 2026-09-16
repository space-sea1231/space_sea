#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n;
ll c;
ll g(ll s,int d){
    return d==1?((s>=-c)+(s>=c)):-((s<=-c)+(s<=c));
}
void work(){
    cin>>n>>c;
    ll a=0,b=0,d=0,e=0;
    for(int i=0;i<n;i++){
        int t,u,v;cin>>t>>u>>v;
        if(!t)continue;
        int x=(t==u)?1:-1,y=(t==v)?1:-1;
        if(x==1 && y==1)a++;
        else if(x==1)b++;
        else if(y==1)d++;
        else e++;
    }
    if(b<d)swap(b,d);

    ll ans=0,s=0,t=0;
    auto add=[&](int x,int y){
        ans+=g(s,x)+g(t,y);
        s+=x;
        t+=y;
    };
    for(int i=1;i<=a;i++)add(1,1);
    for(int i=1;i<=b-d;i++)add(1,-1);
    for(int i=1;i<=e;i++)add(-1,-1);
    if(a>0 && a<c){
        ll L=max(1LL,c-a-(b-d)+1);
        ans+=2*max(0LL,d-L+1);
    }else if(a==c){
        ans+=2*d;
    }else if(a>c){
        ans+=4*d;
    }
    
    cout<<ans<<'\n';
}

int main(){
    // freopen("data.in","r",stdin);
    // freopen("data.out","w",stdout);
    // clock_t start=clock();
    ios::sync_with_stdio(0),cin.tie(0);
    int T;cin>>T;while(T--)work();
    // clock_t end=clock();
    // cerr<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s\n";
}