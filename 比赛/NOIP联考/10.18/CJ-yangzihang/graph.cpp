#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int bit=64;
int a[N], b[N];
bool vis[N];
vector<int> q[bit];
/*
a[i] 原数组中的值
b[i] a[i]二进制状态下的第一位1的位置
*/
int fa[N], n;
int find(int x){
    if (fa[x]==x){
        return x;
    }
    return fa[x]=find(fa[x]);
}
bool cmp(int x,int y){
    return x<y;
}
signed main(){
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
    cin >> n;
    for (int i=1;i<=n;i++){
        cin >> a[i];
        fa[i]=i;
    }//
    sort(a+1,a+n+1,cmp);
    int sum,cnt;
    for (int i=1;i<=n;i++){
        sum=1, cnt=0;
        while(cnt+1<63&&sum*2<=a[i]){
            cnt++;
            sum*=2;
        }
        b[i]=cnt;
        q[cnt].push_back(i);
    }
    int siz, ii, jj;
    for (int i=1;i<=n;i++){
        for (int j=0;j<63;j++){
            if (b[a[i]]==j){
                continue;
            }
            siz=q[j].size();
            for (int k=0;k<siz;k++){
                ii=find(fa[i]);
                jj=find(fa[q[j][k]]);
                fa[ii]=jj;
            }
        }
    }
    cnt=0;
    for (int i=1;i<=n;i++){
        if (vis[fa[i]]){
            continue;
        }
        vis[fa[i]]=1;
        cnt++;
    }
    printf("%lld",cnt);
    return 0;
}