#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t, n, m, L, V;
int d[N], v[N], a[N];
struct node{
    int l, r;
    bool operator < (const node &a){
        return r<a.r;
    }
};
vector<int> test;
vector<node> q;
int speed(int v, int a, int s){
    return v*v+2*a*s;
}
void find(int d, int v, int a){
    int first=lower_bound(test.begin(), test.end(), d)-test.begin();
    if (first>=m){
        return ;
    }
    if (a==0){
        if (v>V){
            q.push_back({first, m-1});
        }
        return ;
    }
    int l=first, r=m-1, ans=-1;
    if (a<0){
        while (l<=r){
            int mid=(l+r)>>1;
            if (speed(v, a, test[mid]-d)>V*V){
                ans=mid;
                l=mid+1;
            }else{
                r=mid-1;
            }
        }
        if (ans!=-1){
            q.push_back({first, ans});
        }
    }
    if (a>0){
        while (l<=r){
            int mid=(l+r)>>1;
            if (speed(v, a, test[mid]-d)>V*V){
                ans=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        if (ans!=-1){
            q.push_back({ans, m-1});
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--){
        q.clear();
        test.clear();
        cin >> n >> m >> L >> V;
        for (int i=1; i<=n; i++){
            cin >> d[i] >> v[i] >> a[i];
        }
        for (int i=1; i<=m; i++){
            int b;
            cin >> b;
            test.push_back(b);
        }
        for (int i=1; i<=n; i++){
            find(d[i], v[i], a[i]);
        }
        sort(q.begin(), q.end());
        int last=-1, cnt=0;
        for (int i=0; i<q.size(); i++){
            if (last<q[i].l){
                last=q[i].r;
                cnt++;
            }
        }
        int size=q.size();
        printf("%d %d\n", size, m-cnt);
    }

    return 0;
}