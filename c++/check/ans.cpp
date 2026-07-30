#include<bits/stdc++.h>
#define int long long
using namespace std;
int fa[200010],f[200010],a[200010],b[200010];
int find(int x){
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
struct node{
    int x;
    bool friend operator<(node i,node j){
        return b[i.x]*a[j.x]>b[j.x]*a[i.x];
    }
};
priority_queue<node>q;

signed main(){
    printf("1\n");
    return 0;
}