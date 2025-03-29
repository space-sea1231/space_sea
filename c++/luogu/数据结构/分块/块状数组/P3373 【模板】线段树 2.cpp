#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n, m, q;
int a[N];
struct Blocking{
    int siz;
    int L[N], R[N];
    int pos[N], sum[N];
    int visa[N], vism[N];
    void Down(int x){
        for (int i=L[x]; i<=R[x]; i++){
            a[i]=(a[i]*vism[x]+visa[x])%q;
        }
        visa[x]=0, vism[x]=1;
    }
    void Add(int l, int r, int w){
        int x=pos[l], y=pos[r];
        if (x==y){
            Down(x);
            for (int i=l; i<=r; i++){
                a[i]=(a[i]+w)%q;
            }
            sum[x]=(sum[x]+(r-l+1)*w)%q;  
        }else{
            Down(x), Down(y);
            for (int i=l; i<=R[x]; i++){
                a[i]=(a[i]+w)%q;
            }
            sum[x]=(sum[x]+(R[x]-l+1)*w)%q;
            for (int i=L[y]; i<=r; i++){
                a[i]=(a[i]+w)%q;
            } 
            sum[y]=(sum[y]+(r-L[y]+1)*w)%q;
            for (int i=x+1; i<=y-1; i++){
                visa[i]=(visa[i]+w)%q;
                sum[i]=(sum[i]+(R[i]-L[i]+1)*w)%q;
            }
        }
    }
    void Mul(int l, int r, int w){
        int x=pos[l], y=pos[r];
        if (x==y){
            Down(x);
            for (int i=l; i<=r; i++){
                sum[x]=(sum[x]+(a[i]*(w-1)))%q;
                a[i]=(a[i]*w)%q;
            }
        }else{
            Down(x), Down(y);
            for (int i=l; i<=R[x]; i++){
                sum[x]=(sum[x]+(a[i]*(w-1)))%q;
                a[i]=(a[i]*w)%q;
            }
            for (int i=L[y]; i<=r; i++){
                sum[y]=(sum[y]+(a[i]*(w-1)))%q;
                a[i]=(a[i]*w)%q;
            }
            for (int i=x+1; i<=y-1; i++){
                visa[i]=(visa[i]*w)%q;
                vism[i]=(vism[i]*w)%q;
                sum[i]=(sum[i]*w)%q;
            }
        }
    }
    int Query(int l, int r){
        int x=pos[l], y=pos[r];
        int ans=0;
        if (x==y){
            for (int i=l; i<=r; i++){
                ans=(ans+a[i])%q;
            }
            ans=(ans*vism[x]+(r-l+1)*visa[x])%q;
        }else{
            for (int i=l; i<=R[x]; i++){
                ans=(ans+a[i]*vism[x]+visa[x])%q;
            }
            for (int i=L[y]; i<=r; i++){
                ans=(ans+a[i]*vism[y]+visa[y])%q;
            }
            for (int i=x+1; i<=y-1; i++){
                ans=(ans+sum[i])%q;
            }
        }
        return (ans+q)%q;
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
                sum[i]=(sum[i]+a[j])%q;
            }
            vism[i]=1;
        }
    }
}block;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m >> q;
    for (int i=1; i<=n; i++){
        cin >> a[i];
        a[i]%=q;
    }
    block.Init();
    for (int i=1; i<=m; i++){
        int opt;
        cin >> opt;
        if (opt==1){
            int x, y, z;
            cin >> x >> y >> z;
            block.Mul(x, y, z);
        }
        if (opt==2){
            int x, y, z;
            cin >> x >> y >> z;
            block.Add(x, y, z);
        }
        if (opt==3){
            int x, y;
            cin >> x >> y;
            printf("%lld\n", block.Query(x, y));
        }
    }

    return 0;
}