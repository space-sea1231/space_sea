#include <bits/stdc++.h>
using namespace std;
const int N=40;
const int M=6e2+10;
int n, m, cnt, top, ans, top_tmp;
int head[N], to[M], nxt[M];
int in[N], in_topu[N], stk[N], tmp[N];
char c[N];
bool vis[N];
void add(int u ,int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void init(){
    memset(vis, 0, sizeof(vis));
    top=0, top_tmp=0;
}
bool topu(int now){
    init();
    bool flag=1;
    for (int i=0; i<n; i++){
        in_topu[i]=in[i];
        if (in[i]==0){
            stk[++top]=i;
        }
    }
    while (top){
        if (top>1){
            flag=0;
        }
        int u=stk[top];
        top--;
        tmp[++top_tmp]=u;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            in_topu[v]--;
            if (in_topu[v]==0&&vis[v]==0){
                stk[++top]=v;
                vis[v]=1;
            }
        }
    }
    if (top_tmp<n){
        return 0;
    }
    if (flag&&ans==0){
        printf("Sorted sequence determined after %d relations: ", now);
        for (int i=1; i<=n; i++){
            printf("%c", (char)(tmp[i]+'A'));
        }
        printf(".");
        exit(0);
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=m; i++){
        cin >> c;
        int u=c[0]-'A';
        int v=c[2]-'A';
        add(u, v);
        in[v]++;
        if (!topu(i)){
            printf("Inconsistency found after %d relations.", i);
            return 0;
        }
    }
    printf("Sorted sequence cannot be determined.");
    
     return 0;
}