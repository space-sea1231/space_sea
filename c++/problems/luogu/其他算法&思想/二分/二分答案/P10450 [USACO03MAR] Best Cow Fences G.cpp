#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const double INF=(1<<30);
const double eps=1e-7;
int n, m;
double a[N], sum[N];
bool check(double mid){
    for (int i=1; i<=n; i++){
        sum[i]=sum[i-1]+a[i]-mid;
    }
    double minn=INF, tot=-INF;
    for (int i=m; i<=n; i++){
        minn=min(minn, sum[i-m]);
        tot=max(tot, sum[i]-minn);
    }
    if (tot>=0){
        return 1;
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    double l=0, r=INF;
    while (r-l>eps){
        double mid=(l+r)/2;
        if (check(mid)){
            l=mid;
        }else{
            r=mid;
        }
    }
    printf("%d\n", (int)(r*1000));

    return 0;
}