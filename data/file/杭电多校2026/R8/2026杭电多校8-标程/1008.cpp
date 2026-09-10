#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using vt=vector<int>;

const int N=2005;

template<typename tp1,typename tp2>
void ckmx(tp1 &x,const tp2 &y){
    if(x<y)x=y;
}

int T,n,deg[N];
vt lk[N];
vector<pii>rp[N];
ll F[N][N],ans;

struct dat{
    int d[N],f[N],sz[N];

    void dfs(int x){
        sz[x]=1;
        for(int y:lk[x])
            if(y!=f[x]){
                d[y]=d[x]+1;
                f[y]=x;
                dfs(y);
                sz[x]+=sz[y];
            }
    }

    void init(int x){
        f[x]=d[x]=0;
        dfs(x);
        for(int y=1;y<=n;++y)
            rp[d[y]].emplace_back(x,y);
    }
}h1[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int i,k,l,r,x,y;

    for(cin>>T;T--;){
        cin>>n;

        for(x=1;x<=n;++x)
            deg[x]=0;

        for(i=1;i<n;++i){
            cin>>x>>y;
            lk[x].push_back(y);
            lk[y].push_back(x);
            ++deg[x];
            ++deg[y];
        }

        ll mn;
        if(*max_element(deg+1,deg+n+1)==2)
            mn=n+n-1;
        else
            mn=n+1;

        for(x=1;x<=n;++x)
            h1[x].init(x);

        ans=0;

        for(auto at:rp[0]){
            tie(x,y)=at;
            ll v=1,sum=1;
            for(int y:lk[x]){
                v+=sum*h1[x].sz[y];
                sum+=h1[x].sz[y];
            }
            F[x][x]=v;
        }

        for(k=0;k<=n;++k){
            for(auto at:rp[k]){
                tie(x,y)=at;
                ckmx(ans,F[x][y]);

                for(int z:lk[x])
                    if(z!=h1[y].f[x]){
                        l=y,r=z;
                        if(l<r)swap(l,r);
                        ckmx(
                            F[l][r],
                            F[x][y]+
                            1ll*h1[x].sz[z]*h1[z].sz[y]
                        );
                    }

                for(int z:lk[y])
                    if(z!=h1[x].f[y]){
                        l=x,r=z;
                        if(l<r)swap(l,r);
                        ckmx(
                            F[l][r],
                            F[x][y]+
                            1ll*h1[y].sz[z]*h1[z].sz[x]
                        );
                    }
            }
        }

        cout<<mn<<' '<<ans<<'\n';

        for(x=0;x<=n;++x){
            fill(F[x],F[x]+n+1,0);
            rp[x].clear();
        }

        for(x=1;x<=n;++x)
            lk[x].clear();
    }

    return 0;
}
