#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, tim[N];
struct node{
    int x, id;
    bool go, flag;
    bool operator<(const node a)const{
        return x<a.x;
    }
}e[N];
stack<node> s;
int main(){
    freopen("ball.in", "r", stdin);
    freopen("ball.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> e[i].x;
        e[i].flag=1;
        e[i].id=i;
    }
    char c;
    for (int i=1; i<=n; i++){
        cin >> c;
        if (c=='L'){
            e[i].go=0;
        }
        if (c=='R'){
            e[i].go=1;
        }
    }
    sort(e+1, e+n+1);
    node a;
    for (int i=1; i<=n; i++){
        if (e[i].go){
            s.push(e[i]);
        }
        if (!e[i].go){
            if (s.empty()){
                tim[e[i].id]=-1;
                continue;
            }
            a=s.top();
            s.pop();
            tim[a.id]=tim[e[i].id]=(e[i].x-a.x);
        }
    }
    while (!s.empty()){
        a=s.top();
        s.pop();
        tim[a.id]=-1;
    }
    for (int i=1; i<=n; i++){
        printf("%d ", tim[i]);
    }
    return 0;
}
/*
对于小球,如果它前进的方向上没有活着的小球,那它就会一直滚下去
搜一遍,用右滚小球抵消左滚小球.
*/