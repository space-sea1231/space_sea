#include <bits/stdc++.h>
using namespace std;
const int N=2010;
const double eps=1e-8;
struct edge{
    int u,v;
}road[N];
int n,m,st,en;
int tot,first[N],nex[N],out[N];
int deep[N],vis[N],step[N][N];
double f[N][N];
queue <int> q;
void Add(int x,int y)
{
    nex[++tot]=first[x];
    first[x]=tot;
    road[tot].u=x;
    road[tot].v=y;
}
 
double DFS(int x,int y)     //记忆化搜索即可 
{
    if(x==y) return 0.0;        //已经抓到，期望为0 
    if(step[x][y]==y||step[step[x][y]][y]==y) return 1.0;   //下一步即可捉到，期望为1 
    if(!(fabs(f[x][y])<eps)) return f[x][y];     //已经算过 
    double sum=DFS(step[step[x][y]][y],y);	//原地不动 
    for(int i=first[y];i!=-1;i=nex[i])
        sum+=DFS(step[step[x][y]][y],road[i].v);	//枚举选择 
    return f[x][y]=sum/(out[y]+1.0)+1.0;        //可可可以不动,最后加1与扑克同理可证 
}
 
void Get_Step(int point)        //step[i][j]表示当可可在j位置聪聪在i位置时聪聪的选择 
{
    memset(vis,0,sizeof(vis));
    memset(deep,127,sizeof(deep));
    q.push(point);
    vis[point]=1;
    deep[point]=0;
    while(!q.empty()){ 
        int x=q.front();
        vis[x]=0; 
        for(int i=first[x];i!=-1;i=nex[i]){
            int to=road[i].v;
            if(!vis[to]&&deep[to]>deep[x]+1){	
                deep[to]=deep[x]+1;			//更新深度 
                step[to][point]=x;		//记录目标点 
                q.push(to);		//由于深度发生变化，重新入对 
                vis[to]=1;		//标记为已入队 
            }
            else{
                if(deep[to]==deep[x]+1)		
                    if(x<step[to][point]) step[to][point]=x;	//更新为下标更小的点 
            }
        }
        q.pop();
    }
}
 
int main()
{
    memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    scanf("%d%d",&st,&en);
    int x,y;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        Add(x,y); Add(y,x); 
        out[x]++; out[y]++; //统计出度 
    }
    for(int i=1;i<=n;i++)    //枚举每个点,当成可可的位置进行BFS,求解step数组 
        Get_Step(i);
    printf("%.3lf",DFS(st,en));     //记忆化搜索答案易得 
    return 0;
}