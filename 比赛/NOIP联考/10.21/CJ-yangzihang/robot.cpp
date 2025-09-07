#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,m,xx,yy;
int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};
char a[N];
void go(int l,int r){
    int x=0, y=0, now=0;
    for (int i=l; i<=r; i++){//1 2
        if (a[i]=='W'){
            x+=dx[now];
            y+=dy[now];
        }
        if (a[i]=='S'){
            x-=dx[now];
            y-=dy[now];
        }
        if (a[i]=='A'){
            now=(now+3)%4;
        }
        if (a[i]=='D'){
            now=(now+5)%4;
        }
    }
    xx=x,yy=y;
    return;
}
signed main(){
    freopen("robot.in", "r", stdin);
    freopen("robot.out", "w", stdout);
    ios::sync_with_stdio(0);;
    cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    cin >> m;
    int opt,x,l,r;
    char ch;
    for (int i=1; i<=m; i++){
        cin >> opt;
        if (opt==1){
            cin >> x >> ch;
            a[x]=ch;
        }
        if (opt==2){
            cin >> l >> r;
            go(l,r);
            printf("%lld %lld\n", xx,yy);
        }
    }
    return 0;
}