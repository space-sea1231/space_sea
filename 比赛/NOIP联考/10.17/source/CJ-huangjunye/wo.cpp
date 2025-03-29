#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1000006];
bool avil[1000006];
int fact[1000006];
int inv[1000006];
const int mod=998244353;
int qow(int base,int power){
    if(power==1) return base;
    int tmp=qow(base,power>>1);
    if(power&1){
        return 1ll*tmp*tmp%mod*base%mod;
    }
    else{
        return 1ll*tmp*tmp%mod;
    }
}
int n;
int mx;
int ans;
void dfs2(int now,int sum){
    if(now==n*2+1){
        // printf("debug:\n");
        // for(int i=1;i<=2*n;i++){
        //     printf("%d ",a[i]);
        // }
        // printf("\n");
        if(sum==mx){
            ans++;
        }
        return ;
    }
    if(a[now]==0){
        for(int i=1;i<=2*n;i++){
            if(avil[i]){
                a[now]=i;
                avil[i]=0;
                dfs2(now+1,sum+(now%2==0)*abs(a[now]-a[now-1]));
                avil[i]=1;
                a[now]=0;
            }
        }
    }
    else{
        dfs2(now+1,sum+(now%2==0)*abs(a[now]-a[now-1]));
    }
}
void dfs1(int now,int sum){
    if(now==n*2+1){
        mx=max(mx,sum);
        return ;
    }
    if(a[now]==0){
        for(int i=1;i<=2*n;i++){
            if(avil[i]){
                a[now]=i;
                avil[i]=0;
                dfs1(now+1,sum+(now%2==0)*abs(a[now]-a[now-1]));
                avil[i]=1;
                a[now]=0;
            }
        }
    }
    else{
        dfs1(now+1,sum+(now%2==0)*abs(a[now]-a[now-1]));
    }
}
void work(){
    scanf("%d",&n);
    ans=mx=0;
    memset(avil,1,sizeof(avil));
    for(int i=1;i<=n*2;i++){
        scanf("%d",&a[i]);
        avil[a[i]]=0;
    }
    dfs1(1,0);
    // printf("Debug:%d\n",mx);
    dfs2(1,0);
    printf("%d\n",ans);
}
int main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--){
        work();
    }
    return 0;
}
/*
1
3
2 3 6 0 0 0
*/