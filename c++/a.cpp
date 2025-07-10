#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
const int CN = 160;
class fs{
  public: int to,nxt; void init(int t,int n) {to=t;nxt=n;}
}E[CN * 2];
int hd[CN],ecnt = 0;
void add(int x,int y) {E[++ecnt].init(y,hd[x]);hd[x]=ecnt;}

int n,P,ans,sum[CN],f[CN][CN]; // sum[u] 表示子树 u 的大小
void dfs(int u,int p){
    sum[u] = 1; f[u][1] = 0; // 初始时不考虑子树，因此 f[u][1] = 1
    for(int k=hd[u];k;k=E[k].nxt){
        int v = E[k].to;
        if(v == p) continue;
        dfs(v, u); // 求出子树的答案
        sum[u] += sum[v]; // 累加大小
        
        for(int s=sum[u]; s; s--){ // 考虑背包问题的更新方式，那么一定要每次都更新一下
            f[u][s] += 1; // 实际上是 f[u][k][s] = f[u][k-1][s] + 1 ，滚动了 k 这一维
            for(int sv=0;sv<=min(s-1, sum[v]);sv++) // s-1 为了强制选根
                f[u][s] = min(f[u][s], f[u][s - sv] + f[v][sv]);
        }
    }    
}

int main()
{
    //freopen("p1272.in","r",stdin);

    scanf("%d%d",&n,&P);
    for(int i=1;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        add(x,y); add(y,x);
    }

    memset(f,0x3f,sizeof(f));
    dfs(1,0);
    ans = f[1][P]; for(int i=2;i<=n;i++) ans = min(ans, f[i][P] + 1); // 加上与父亲之间的那条边
    printf("%d", ans);

    return 0;
}
