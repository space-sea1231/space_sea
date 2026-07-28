#include <bits/stdc++.h>
using namespace std;
const int Mod=998244353;
const int N=2e6+10;
int t, n;
int a[N], b[N], cnt, sum, tot;
bool ton[N], vis[N];
void check(){
    int cnm=0;
    for (int i=1; i<=n; i+=2){
        cnm=(cnm+abs(a[i]-a[i+1]))%Mod;
    }
    if (cnm==sum){
        tot++;
    }
}
void serch(int dep){
    cerr << dep << endl;
    if (dep==n+1){//到了
        check();
        return;
    }
    if (a[dep]){//当前位置有固定值了
        serch(dep+1);
        return;
    }
    for (int i=1; i<=cnt; i++){
        if (vis[i]){
            continue;
        }
        vis[i]=1;
        a[dep]=b[i];
        serch(dep+1);
        a[dep]=0;
        vis[i]=0;
    }
}
int main(){
    freopen("wo.in", "r", stdin);
    freopen("wo.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--){
        for (int i=1; i<N; i++){
            a[i]=0;
            ton[i]=0;
            b[i]=0;
        }
        cin >> n;
        n*=2;
        sum=cnt=tot=0;
        for (int i=1; i<=n; i++){
            cin >> a[i];
            if (a[i]){//桶存数
                ton[a[i]]=1;
            }
        }
        for (int i=1; i<=n; i++){
            if (!ton[i]){//将可以用的数存起来
                b[++cnt]=i;
            }
        }
        int l=1, r=cnt;
        for (int i=1; i<=n; i+=2){
            if (a[i]&&a[i+1]){//都有数,直接加
                sum=(sum+abs(a[i]-a[i+1]))%Mod;
            }
            if (a[i]&&a[i+1]==0){//只有一个有数
                int l_ans=abs(a[i]-b[l]);
                int r_ans=abs(a[i]-b[r]);
                if (l_ans<r_ans){
                    r--;
                    sum=(sum+r_ans)%Mod;
                }
                if (l_ans>r_ans){
                    l++;
                    sum=(sum+r_ans)%Mod;
                }
            }
            if (a[i]==0&&a[i+1]){//只有一个有数
                int l_ans=abs(a[i+1]-b[l]);
                int r_ans=abs(a[i+1]-b[r]);
                if (l_ans<r_ans){
                    r--;
                    sum=(sum+r_ans)%Mod;
                }
                if (l_ans>r_ans){
                    l++;
                    sum=(sum+r_ans)%Mod;
                }
            }
            if (a[i]==0&&a[i+1]==0){//只有一个有数
                sum=(sum+abs(b[l]-b[r]))%Mod;
                l++;
                r--;
            }
        }
        serch(1);
        printf("%d\n", tot);
    }

    return 0;
}