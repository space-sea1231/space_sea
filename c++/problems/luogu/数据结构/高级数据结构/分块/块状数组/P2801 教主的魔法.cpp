#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n, m;
struct Blocking{
    int L[N], R[N], tmp[N];
    int sum[N], pos[N], vis[N];
    void Sort(int x){
        for (int i=L[x]; i<=R[x]; i++){
            tmp[i]=sum[i];
        }
        sort(tmp+L[x], tmp+R[x]+1);
    }
    void Add(int l, int r, int w){
        int x=pos[l], y=pos[r];
        if (x==y){
            for (int i=l; i<=r; i++){
                sum[i]+=w;
            }
            Sort(x);
        }else{
            for (int i=l; i<=R[x]; i++){
                sum[i]+=w;
            }
            for (int i=L[y]; i<=r; i++){
                sum[i]+=w;
            }
            for (int i=x+1; i<=y-1; i++){
                vis[i]+=w;
            }
            Sort(x);
            Sort(y);
        }
    }
    int Query(int l, int r, int w){
        int x=pos[l], y=pos[r], ans=0;
        if (x==y){
            for (int i=l; i<=r; i++){
                if (sum[i]+vis[x]>=w){
                    ans++;
                }
            }
        }else{
            for (int i=l; i<=R[x]; i++){
                if (sum[i]+vis[x]>=w){
                    ans++;
                }
            }
            for (int i=L[y]; i<=r; i++){
                if (sum[i]+vis[y]>=w){
                    ans++;
                }
            }
            for (int i=x+1; i<=y-1; i++){
                int ll=L[i], rr=R[i], anss=R[i]+1;
                while (ll<=rr){
                    int mid=(ll+rr)>>1;
                    if (tmp[mid]+vis[i]>=w){
                        rr=mid-1;
                        anss=mid;
                    }else{
                        ll=mid+1;
                    }
                }
                ans+=R[i]-anss+1;
            }
        }
        return ans;
    }
    void Init(){
        int siz=sqrt(n);
        for (int i=1; i<=siz; i++){
            L[i]=(i-1)*siz+1;
            R[i]=i*siz;
        }
        if (R[siz]<n){
            siz++;
            L[siz]=R[siz-1]+1;
            R[siz]=n;
        }
        for (int i=1; i<=n; i++){
            tmp[i]=sum[i];
        }
        for (int i=1; i<=siz; i++){
            sort(tmp+L[i], tmp+R[i]+1);
            for (int j=L[i]; j<=R[i]; j++){
                pos[j]=i;
            }
        }
    }
}block;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> block.sum[i];
    }
    block.Init();
    for (int i=1; i<=m; i++){
        char opt;
        int x, y, z;
        cin >> opt >> x >> y >> z;
        if (opt=='M'){
            block.Add(x, y, z);
        }
        if (opt=='A'){
            printf("%d\n", block.Query(x, y, z));
        }
    }

    return 0;
}