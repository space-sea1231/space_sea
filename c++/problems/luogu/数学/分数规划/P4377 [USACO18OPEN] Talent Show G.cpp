#include <bits/stdc++.h>
using namespace std;
const int N=3e2+10;
const int W=1e3+10;
const double INF=1<<30;
const double eps=1e-6;
int n, m;
int a[N], b[N];
double c[N], dp[W];
bool check(double mid){
    for (int i=1; i<=n; i++){
        c[i]=(double)a[i]-mid*b[i];
    }
    for (int i=1; i<=m; i++){
        dp[i]=-INF;
    }
    for (int i=1; i<=n; i++){
        for (int j=m; j>=0; j--){
            if (j+b[i]>=m){
                dp[m]=max(dp[m], dp[j]+c[i]);
            }else{
                dp[(j+b[i])]=max(dp[(int)(j+b[i])], dp[j]+c[i]);
            }
        }
    }
    if (dp[m]>=0){
        return 1;
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> b[i] >> a[i];
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
    printf("%d", (int)(l*1000));

    return 0;