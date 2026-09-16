#include<bits/stdc++.h>
#define x first
#define y second
#define all(x) x.begin(),x.end()
#define pr(x) cerr << #x << ":" << x << endl
#define ee exit(0)
#define de cerr << "------------" << endl
#define prl(w,n) for(int _=1;_<=n;_++) cerr << w[_] << " \n"[_==n];
#define prm(w,n,m)	for(int _=1;_<=n;_++) for(int __=1;__<=m;__++)	cerr << w[_][__] << " \n"[__==m];
#define endl '\n'
#define int long long
using namespace std;

template <typename T>
inline void rd(T &x){
	x = 0;char ch = getchar();bool f = 0;
	while(ch < '0' || ch > '9'){if(ch == '-')f = 1;ch = getchar();}
	while(ch >= '0' && ch <= '9')x = (x<<1) + (x<<3) + (ch^48),ch=getchar();
	if(f)x = -x;                                       
}
template <typename T,typename ...Args>
inline void rd(T &tmp,Args &...tmps){rd(tmp);rd(tmps...);}

typedef pair<int,int> pii;
const int N = 200010,M = 2*sqrt(N),INF = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353 + 1e9 + 7;
const int len = sqrt(N);
#define get(x) ((x-1)/len+1)

struct query
{
	int l,r,k,id;
	bool operator<(const query &t) const
	{
		if(get(l) == get(t.l)) 
			return (get(l) & 1) ? r < t.r : r > t.r;
		else return l < t.l;
	}
}q[N];

int a[N],t[N];
int ans[N];
int cnt[M][N];
int mn[M];
int w[N];
int n,m,Q;

void add(int i)
{
	int x = t[i];
	int pos = get(x);
	cnt[pos][w[x]]--;
	cnt[pos][w[x]+a[i]]++;
	if(a[i] == -1)
		mn[pos] = min(mn[pos],w[x]+a[i]);
	else if(!cnt[pos][w[x]] && w[x] == mn[pos])
		mn[pos]++;
	w[x] += a[i];
}

void del(int i)
{
	int x = t[i];
	int pos = get(x);
	cnt[pos][w[x]]--;
	cnt[pos][w[x]-a[i]]++;
	if(a[i] == 1)
		mn[pos] = min(mn[pos],w[x]-a[i]);
	else if(!cnt[pos][w[x]] && w[x] == mn[pos])
		mn[pos]++;
	w[x] -= a[i];
}

int query(int p)
{
	p += 1e5;
	for(int i=1;i<=get(m);i++)
		if(mn[i] <= p)
		{
			for(int j=(i-1)*len+1;;j++)
				if(w[j] <= p)
					return j;
		}
	return -1;
}

string solve()
{
	rd(n,m,Q);
	for(int i=1;i<=n;i++) rd(t[i]);
	for(int i=1;i<=n;i++) rd(a[i]);
	for(int i=1;i<=get(m);i++)
		for(int j=100000-n;j<=100000+n;j++)
			cnt[i][j] = 0;
	for(int i=1;i<=m;i++) w[i] = 1e5,cnt[get(i)][100000]++;
	for(int i=1;i<=get(m);i++) mn[i] = 1e5;
	for(int i=1;i<=Q;i++)
	{
		rd(q[i].l,q[i].r,q[i].k);
		q[i].id = i;
	}
	sort(q+1,q+1+Q);
	int i=1,j=0;
	for(int p=1;p<=Q;p++)
	{
		int l = q[p].l,r = q[p].r,k = q[p].k;
		while(j < r) add(++j);
		while(i > l) add(--i);
		while(j > r) del(j--);
		while(i < l) del(i++);
		ans[q[p].id] = query(k);
	}
	for(int i=1;i<=Q;i++)
		cout << ans[i] << endl;
	return "";
}

signed main()
{
//	freopen("data.in","r",stdin);
//	freopen("ans.out","w",stdout);	
	int T = 1;
	rd(T);
	while(T--)
	{
		string t = solve();
		if(t.size()) cout << t << endl;
	}
	
	
	return 0;
}
