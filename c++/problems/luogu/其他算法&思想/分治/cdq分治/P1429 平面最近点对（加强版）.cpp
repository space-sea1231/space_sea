#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int INF=(1<<30);
int n;
int tmp[N];
struct node{
    double x, y;
    bool operator <(const node &a){
        if (x==a.x){
            return y>a.y;
        }
        return x<a.x;
    }
}e[N];
bool cmp(int i, int j){
    return e[i].y<e[j].y;
}
double dist(int i, int j){
    double x=abs(e[i].x-e[j].x)*abs(e[i].x-e[j].x);
    double y=abs(e[i].y-e[j].y)*abs(e[i].y-e[j].y);
    return sqrt(x+y);
}
double Merge(int l, int r){
    double dis=INF;
    if (l==r){
        return dis;
    }
    int mid=(l+r)>>1;
    double dis_l=Merge(l, mid);
    double dis_r=Merge(mid+1, r);
    dis=min(dis_l, dis_r);
    int top=0;
    for (int i=l; i<=r; i++){
        if (fabs(e[mid].x-e[i].x)<dis){
            tmp[++top]=i;
        }
    }
    sort(tmp+1, tmp+top+1, cmp);
    for (int i=1; i<=top; i++){
        for (int j=i+1; j<=top; j++){
            if (e[tmp[i]].y-e[tmp[j]].y<dis){
                double dis_tmp=dist(tmp[i], tmp[j]);
                dis=min(dis, dis_tmp);
            }
        }
    }
    return dis;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> e[i].x >> e[i].y;
    }
    sort(e+1, e+n+1);
    double ans=Merge(1, n);
    printf("%.4lf\n", ans);

    return 0;
}