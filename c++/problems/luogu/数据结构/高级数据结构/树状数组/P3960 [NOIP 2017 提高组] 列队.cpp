#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
int n, m, Q, mx;
int x[N], y[N], pre[N];
struct Node{
    int val, id;
};
vector<Node> q[N];
vector<int> p[N];
struct Binary_Indexed_Tree{
    const int M=6e5+10;
    int num[N<<1];
    int lowbit(int x){
        return x&-x;
    }
    void Add(int x, int w){
        for (int i=x; i<=M; i+=lowbit(i)){
            num[i]+=w;
        }
    }
    int Query(int x){
        int ans=0;
        for (int i=x; i>=1; i-=lowbit(i)){
            ans+=num[i];
        }
        return ans;
    }
    int select(int x){
        int l=0, r=M, ans=M;
        while (l<=r){
            int mid=(l+r)>>1;
            if (Query(mid)>=x){
                ans=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        return ans;
    }
    Binary_Indexed_Tree(){
        for (int i=1; i<=M; i++){
            Add(i, 1);
        }
    }
}tree;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m >> Q;
    for (int i=1; i<=Q; i++){
        cin >> x[i] >> y[i];
        if (y[i]!=m){
            q[x[i]].push_back({y[i], i});
        }
    }
    for (int i=1; i<=n; i++){
        for (Node j:q[i]){
            pre[j.id]=tree.select(j.val);
            tree.Add(pre[j.id], -1);
        }
        for (Node j:q[i]){
            tree.Add(pre[j.id], 1);
        }
    }
    for (int i=1; i<=Q; i++){
        int pos=tree.select(x[i]), last, ans;
        tree.Add(pos, -1);
        if (pos<=n){
            last=pos*m;
        }else{
            last=p[0][pos-n-1];
        }
        if (y[i]!=m){
            p[x[i]].push_back(last);
            if (pre[i]<m){
                ans=(x[i]-1)*m+pre[i];
            }else{
                ans=p[x[i]][pre[i]-m];
            }
        }else{
            ans=last;
        }
        printf("%lld\n", ans);
        p[0].push_back(ans);
    }

    return 0;
}