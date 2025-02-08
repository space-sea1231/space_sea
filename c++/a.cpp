#include<bits/stdc++.h>
using namespace std;
const int maxn = 10021;
const int maxm = 10021;
const int inf = 2147483647;
int n,m,cnt,str,end,tot = -1,maxcost,p;
int head[maxn],pre[maxn],last[maxn],flow[maxn],d[maxn],pos[50][50];
bool vis[maxn],v[maxn];
struct node
{
	int net,va,cost,to;
}data[maxm<<3];

int read() 
{
	int res=0;
	char c=getchar();
	while (c<'0'||c>'9')
		c=getchar();
	while (c>='0'&&c<='9')
	{
		res=res*10+c-'0';
		c=getchar();
	}
	return res;
}

void add(int a,int b,int va,int cost)
{
	data[++tot].cost = cost;
	data[tot].net = head[a];
	data[tot].to = b;
	data[tot].va = va;
	head[a] = tot;
	data[++tot].cost = -cost;
	data[tot].net = head[b];
	data[tot].to = a;
	data[tot].va = 0;
	head[b] = tot;
}

bool SPFA()
{
	memset(d,0x3f,sizeof(d));
	memset(flow,0x3f,sizeof(flow));
	memset(vis,0,sizeof(vis));
	queue<int> q;
	q.push(str);
	vis[str] = 1;
	d[str] = 0;
	pre[end] = -1;
	while(!q.empty())
	{
		int from = q.front();q.pop();
		vis[from] = 0;
		for(int i=head[from];i!=-1;i=data[i].net)
		{
			int to = data[i].to ;
			int va = data[i].va ;
			int cost = data[i].cost ;
			if(va&&d[to]>d[from]+cost)
			{
				d[to] = d[from]+cost;
				pre[to] = from; 
				last[to] = i;
				flow[to] = min(flow[from],va); 
				if(!vis[to])
				{
					vis[to] = 1;
					q.push(to);
				}
			}
		}
	}
	return pre[end] != -1;
}

void MCMF()
{
	while(SPFA())
	{
		int now = end;
		maxcost += flow[end]*d[end];
		while(now!=str)
		{
			data[last[now]].va -= flow[end];
			data[last[now]^1].va += flow[end];
			now = pre[now];
		}
	}
}

void print(int id,int x)
{
	int temp = x - 2 * n * m;//真实的坐标点
	for(int i=head[x];i!=-1;i=data[i].net)
	{
		int to = data[i].to ;
		int va = data[i].va ;
		if(!va)	continue;//表示这条边已经不能有车通过了 
		int tt = to - 2 * n * m;
		if(temp+1==tt)	printf("%d 1\n",id);//向右 
		else			printf("%d 0\n",id);//向下 
		data[i].va--;
		print(id,to);
		break;
	}
}

int main()
{
	memset(head,-1,sizeof(head));
	cnt = read();m = read();n = read();
	str = 3 * n * m + 1;end = 3 * n * m + 2;
	//区间[1,n*m]内是入点，(n*m,2*n*m]是出点，(2*n*m,3*n*m]是新图上的点 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			pos[i][j] = ++p;//先给每个点一个编号 
	add(str,1,cnt,0);
	add(2*n*m,end,cnt,0);//对应分析4 
	for(int i=1;i<=n;i++)//对应分析2 
	{
		for(int j=1;j<=m;j++)
		{
			int x = read();
			if(x==2)	add(pos[i][j],pos[i][j]+n*m,1,-1);
			if(x!=1)	add(pos[i][j],pos[i][j]+n*m,inf,0);
			else	v[pos[i][j]] = 1;//标记一下不能走的边 
		}
	}
	for(int i=1;i<=n;i++)//对应分析3 
		for(int j=2;j<=m;j++)
			add(pos[i][j-1]+n*m,pos[i][j],inf,0);
	for(int i=2;i<=n;i++)
		for(int j=1;j<=m;j++)
			add(pos[i-1][j]+n*m,pos[i][j],inf,0);
	MCMF();//愉快地跑一边MCMF，其中过程很常规 
	for(int x=1+n*m;x<2*n*m;x++)
	{//枚举出点 
		if(v[x-n*m])	continue;//跳过障碍 
		for(int i=head[x];i!=-1;i=data[i].net)
		{
			int va = data[i].va ;
			int to = data[i].to ;
			if(to+n*m==x)	continue;//去掉连向自身的入点 
			if(va==inf)	continue;//去掉不会有车经过的边 
			if(to!=end)
				add(x+m*n,to+2*n*m,inf-va,0);
		}
	}
	for(int i=1;i<=cnt;i++)//dfs求解即可 
		print(i,1+2*n*m);
	return 0;
}
