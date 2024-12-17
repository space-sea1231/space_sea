#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[2000010],jc[2000010];
const int Mod=998244353;
int quick_pow(int x,int y){
    int res=1;
    while(y){
        if(y&1){
            res=res*x%Mod;
        }
        x=x*x%Mod;
        y>>=1;
    }
    return res;
}
bool aa[2000010];
int bb[2000010],yuan[2000010];

signed main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    int T;
    cin>>T;
    jc[0]=1;
    for(int i=1;i<=2e6;i++)jc[i]=jc[i-1]*i%Mod;
    // for(int i=0;i<=2e6;i++)ni[i]=quick_pow(jc[i],Mod-2);
    while(T--){
        memset(aa,0,sizeof(aa));
        int n;
        cin>>n;
        for(int i=1;i<=2*n;i++){
            cin>>a[i];
        }
        int tot=0,cntt=0;
        for(int i=1;i<=2*n;i+=2){
            int x=a[i],y=a[i+1];
            if(x&&y){
                aa[x]=aa[y]=1;
            }
            else{
                yuan[++cntt]=x,yuan[++cntt]=y;
            }
        }
        for(int i=1;i<=2*n;i++)if(!aa[i])bb[++tot]=i;
        sort(bb+1,bb+tot+1);
        int wei=bb[tot/2];
        int shengx=tot/2,shengd=tot/2,ge0=0;
        // cout<<shengx<<" "<<shengd<<" "<<wei<<"\n";
        for(int i=1;i<=cntt;i+=2){
            // cout<<yuan[i]<<" "<<yuan[i+1]<<"\n";
            if(yuan[i]==yuan[i+1]){
                ge0++;
            }
            // cout<<yuan[i]<<" "<<wei<<"\n";
            if(yuan[i]<=wei&&yuan[i])shengx--;
            if(yuan[i+1]<=wei&&yuan[i+1])shengx--;
            if(yuan[i]>wei)shengd--;
            if(yuan[i+1]>wei)shengd--;
        }
        // cout<<shengx<<" "<<shengd<<" "<<ge0<<"\n";
        cout<<jc[shengx]*jc[shengd]%Mod*quick_pow(2,ge0)%Mod<<"\n";
    }
    return 0;
}