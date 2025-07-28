#include <bits/stdc++.h>
using namespace std;
const int N=60;
int n, num;
int match[N];
bool vis[N], edge[N][N];
struct shape{
    int x_min, x_max, y_min, y_max;
}e[N];
void init(){
    memset(match, 0, sizeof(match));
    memset(edge, 0, sizeof(edge));
}
bool check(int x, int y, int z){
    return (e[z].x_min<=x&&x<=e[z].x_max)&&(e[z].y_min<=y&&y<=e[z].y_max);
}
bool dfs(int u){
    for (int v=1; v<=n; v++){
        if (!vis[v]&&edge[u][v]){
            vis[v]=1;
            if (!match[v]||dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
int go(){
    int sum=0;
    memset(match, 0, sizeof(match));
    for (int i=1; i<=n; i++){
        memset(vis, 0, sizeof(vis));
        if (dfs(i)){
            sum++;
        }
    }
    return sum;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    while (cin >> n&&n){
        init();
        printf("Heap %d\n", ++num);
        for (int i=1; i<=n; i++){
            cin >> e[i].x_min >> e[i].x_max >> e[i].y_min >> e[i].y_max;
        }
        for (int i=1; i<=n; i++){
            int x, y;
            cin >> x >> y;
            for (int j=1; j<=n; j++){
                if (check(x, y, j)){
                    edge[i][j]=1;
                }
            }
        }
        int ans=go();
        bool flag=0;
        for (int v=1; v<=n; v++){
            for (int u=1; u<=n; u++){
                if (edge[u][v]){
                    edge[u][v]=0;
                    int tmp=go();
                    if (tmp!=ans){
                        if (flag){
                            printf(" ");
                        }
                        flag=1;
                        printf("(%c,%d)", 'A'+v-1, u);

                    }
                    edge[u][v]=1;
                }
            }
        }
        if (!flag){
            printf("none");
        }
        printf("\n\n");
    }

    return 0;
}