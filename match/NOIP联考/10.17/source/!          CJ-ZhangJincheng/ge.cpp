/*
微笑面对危险，暴力成真不会遥远！鼓起勇气，砥砺向前，奇迹一定会出现！
超级棒棒糖，给我彩虹的光芒！关键时候帮我忙，给我勇气和力量。
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 20
const int p=998442353;
int t,n,m,a[N][N],dis[N][N],ans,minn,A[200010],B[200010],diss[N][N],T;
int ksm(int a,int b){
    int y=a,t=1;
    while(b){
        if(b&1){
            t=t*y%p;
        }
        y=y*y%p;
        b>>=1;
    }
    return t;
}
int C(int n,int m){
    return A[n]*B[n-m]%p*B[m]%p;
}
bool vis[N];
vector<int>v;
void dfs(int x,int now,int sum,int tim){
    if(sum>minn){
        return;
    }
    if(x==n){
        if(sum==minn){
            ans=(ans+tim%p)%p;
        }
        else{
            if(sum<minn){
                ans=tim%p;
                minn=sum;
            }
        }
        return;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=1;
            v.push_back(i);
            dfs(x+1,i,sum+dis[now][i],tim*diss[now][i]%p);
            vis[i]=0;
            v.pop_back();
        }
    }
}
signed main(){
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
    A[0]=1;
    B[0]=1;
    for(int i=1;i<=100000;i++){
        A[i]=A[i-1]*i%p;
        B[i]=ksm(A[i],p-2);
    }
    cin>>t;
    T=t;
    while(t--){
        minn=LONG_LONG_MAX;
        ans=0;
        memset(vis,0,sizeof(vis));
        cin>>m>>n;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
            }
        }
        if(m==1){
            vector<int>v;
            for(int i=1;i<=n;i++){
                v.push_back(a[i][1]);
            }
            sort(v.begin(),v.end());
            int minn=LONG_LONG_MAX,ans=0;
            for(int i=0;i<v.size();i++){
                int x;
                cin>>x;
                if(x==1){
                    if(v[i]-v[0]+v[n-1]-v[0]<minn){
                        minn=v[i]-v[0]+v[n-1]-v[0];
                        ans=1;
                    }
                    else{
                        if(v[i]-v[0]+v[n-1]-v[0]==minn){
                            ans++;
                        }
                    }
                    if(v[n-1]-v[i]+v[n-1]-v[0]<minn){
                        minn=v[n-1]-v[i]+v[n-1]-v[0];
                        ans=1;
                    }
                    else{
                        if(v[n-1]-v[i]+v[n-1]-v[0]==minn){
                            ans++;
                        }
                    }
                }
            }
            if(minn==LONG_LONG_MAX){
                cout<<"NIE\n";
            }
            else{
                cout<<minn<<' '<<ans<<endl;
            }
            continue;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int s=0;
                for(int k=1;k<=m;k++){
                    s+=(int)(abs(a[i][k]-a[j][k]));
                }
                dis[i][j]=s;
                diss[i][j]=1;
                for(int k=1;k<=m;k++){
                    diss[i][j]=(diss[i][j]*C(s,abs(a[i][k]-a[j][k]))%p)%p;
                    s-=(abs(a[i][k]-a[j][k]));
                }
            }
        }
        for(int i=1;i<=n;i++){
            int x;
            cin>>x;
            if(x==1){
                vis[i]=1;v.push_back(i);
                dfs(1,i,0,1);
                vis[i]=0;v.pop_back();
            }
        }
        if(minn==INT_MAX){
            cout<<"NIE\n";
        }
        else{
            cout<<minn<<' '<<ans<<endl;
        }
    }
    return 0;
}