#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n, m;
int a[N];
struct Blocking{
    int siz;
    int pos[N], sum[N], vis[N];
    int L[N], R[N];
    void Add(int x, int y, int z){
        int l=pos[x], r=pos[y];
        if (l==r){
            for (int i=x; i<=y; i++){
                a[i]+=z;
            }
            sum[l]+=(y-x+1)*z;  
        }else{
            for (int i=l+1; i<=r-1; i++){
                vis[i]+=z;
            }
            for (int i=x; i<=R[l]; i++){
                a[i]+=z;
            }
            sum[l]+=(R[l]-x+1)*z;
            for (int i=L[r]; i<=y; i++){
                a[i]+=z;
            }
            sum[r]+=(y-L[r]+1)*z;
        }
    }
    int Query(int x, int y){
        int l=pos[x], r=pos[y];
        int ans=0;
        if (l==r){
            for (int i=x; i<=y; i++){
                ans+=a[i];
            }
            ans+=(y-x+1)*vis[l];
        }else{
            for (int i=l+1; i<=r-1; i++){
                ans+=sum[i]+vis[i]*(R[i]-L[i]+1);
            }
            for (int i=x; i<=R[l]; i++){
                ans+=a[i];
            }
            ans+=(R[l]-x+1)*vis[l];
            for (int i=L[r]; i<=y; i++){
                ans+=a[i];
            }
            ans+=(y-L[r]+1)*vis[r];
        }
        return ans;
    }
    void Init(){
        siz=sqrt(n);
        for (int i=1; i<=n; i++){
            L[i]=(i-1)*siz+1;
            R[i]=i*siz;
        }
        if (R[siz]<n){
            siz++;
            L[siz]=R[siz-1]+1;
            R[siz]=n;
        }
        for (int i=1; i<=siz; i++){
            for (int j=L[i]; j<=R[i]; j++){
                pos[j]=i;
                sum[i]+=a[j];
            }
        }
    }
}e;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    e.Init();
    for (int i=1; i<=m; i++){
        char opt;
        cin >> opt;
        if (opt=='C'){
            int x, y, z;
            cin >> x >> y >> z;
            e.Add(x, y, z);
        }
        if (opt=='Q'){
            int x, y;
            cin >> x >> y;
            printf("%lld\n", e.Query(x, y));
        }
    }
    return 0;
}