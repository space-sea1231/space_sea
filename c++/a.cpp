#include <cstdio>
#include <cctype>
#include <cstring>
inline int getint()
{
	int res = 0, neg = 0, ch = getchar();
	//亲测多种手写isdigit都比<cctype>的isdigit慢
    //更快者欢迎私信 
	while(!(isdigit(ch) || ch == '-') && ch != EOF)
		ch = getchar();
	if(ch == '-')
		neg = 1;
	while(isdigit(ch))
		res = (res << 3) + (res << 1) + (ch - '0'), ch = getchar();
	return neg ? -res : res;
}
#define re register
#define LL long long
#define INF 2147483647
inline LL min(LL x, LL y) {return x < y ? x : y; }
inline LL abs(LL x) {return x < 0 ? -x : x; }
//inline也才比<algorithm>快一点。宏定义日常写挂

int n;
int a[40010], b[40010];
int Minof[40010], len = 0, Longest[40010];

int first[40010], to[40010], nxt[40010], cnt = 0;
LL f[40010];
LL sumL[40010], sumR[40010];

inline void addE(int u, int v)
{
	++cnt;
	to[cnt] = v;
	nxt[cnt] = first[u];
	first[u] = cnt;
}

int main()
{
	n = getint();
	for(re int i = 1; i <= n; ++i)
		a[i] = getint(), b[i] = a[i]-i;
	//想要保留i和j，前提是他们中间能好好放东西 
	//保留的数目越多越好
	
	b[n+1] = INF;
	for(re int i = 1; i <= n+1; ++i)
	{
		int l = 0, r = len;
		while(l < r)
		{
			int mid = (l + r + 1) >> 1;
			if(Minof[mid] <= b[i])
				l = mid;
			else
				r = mid - 1;
		}
		if(l == len) 
			++len;
			
		Longest[i] = l+1;
		addE(Longest[i], i);
		//以i结尾的最长不降子序列长度为Longest[i]。
		//如果b[j]想拼上合适的b[i]，就去前面找长度为Longest[b[j]]-1且能接上的。
		//因此要记录各个长度的子序列的结尾。用vector会更直观

		Minof[l+1] = b[i];
	}
	addE(0, 0);//这么做因为：长度为1的最长不下降子序列的前面几个数也要处理 
	printf("%d\n", n-(len-1));
	
	memset(f, 20, sizeof(f));
	
	b[0] = -INF; //将自动处理“真正的最长不降子序列”前面的几个数 
	f[0] = 0;//把前i个数，改成单调不降子序列且该序列以i结尾的最小代价
	for(re int i = 1; i <= n+1; ++i)//末尾多一个INF，然后依然是把序列变成不下降，
	//将自动处理“真正的最长不降子序列”的后面几个数（也要改啊） 
	{
		for(re int p = first[Longest[i]-1]; p; p = nxt[p])//枚举长度为“b[j]的长度-1”的所有b[i] 
		{
			int u = to[p];
			if(u > i || b[u] > b[i])//嗯，虽然它的长度确实是“我的长度-1”，但可能我并不能接在它后面 
				continue;
			
			//下面注意利用前缀和 
			sumL[u] = 0;//最小代价形态在“i____--------j” 
			for(re int k = u+1; k <= i-1; ++k)
				sumL[k] = sumL[k-1] + abs(b[k] - b[u]);
			//u+1 to k     
			
			//k+1 to i-1
			sumR[i-1] = 0;
			for(re int k = i-2; k >= u; --k)
				sumR[k] = sumR[k+1] + abs(b[k+1] - b[i]);
			//这里求前缀和的时候要弄清楚…… 
			
			for(re int k = u; k <= i-1; ++k)
				f[i] = min(f[i], f[u] + sumL[k] + sumR[k]);
		}	
	}
	//题解看懂，但后半段代码看不懂就打个记忆化搜索好了 
	
	printf("%lld\n", f[n+1]);
	return 0;
}
