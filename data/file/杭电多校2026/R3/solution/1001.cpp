#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double dou;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mapa make_pair
typedef long double ld;
typedef unsigned long long ull;
#define ep emplace_back
template <typename T>inline void read(T &x){
	x=0;char c=getchar();bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0'&&c<='9';c=getchar())
	x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}
const int N=1e6+50, mod=998244353;
int T, n, m;
struct SA{
	char s[N];
    int buc[N], rk[N], sa[N], od[N], id[N], ht[21][N], w, p;
    bool eq(int x, int y) {
        return od[x] == od[y] && od[x + w] == od[y + w];
    }
    void getSA() {
		int m=2;
		buc[1]=buc[2]=0;
        for (int i = 1; i <= n; ++i)
            ++buc[rk[i] = s[i]];
        for (int i = 1; i <= m; ++i)
            buc[i] += buc[i - 1];
        for (int i = n; i; --i)
            sa[buc[rk[i]]--] = i;
        for (int i = 1; i <= m; ++i)
            buc[i] = 0;
        w = 1;
        p = 0;
        while (true) {
            for (int i = n; i > n - w; --i)
                id[++p] = i;
            for (int i = 1; i <= n; ++i)
                if (sa[i] > w)
                    id[++p] = sa[i] - w;
            for (int i = 1; i <= n; ++i)
                ++buc[od[i] = rk[i]];
            for (int i = 1; i <= m; ++i)
                buc[i] += buc[i - 1];
            for (int i = n; i; --i)
                sa[buc[rk[id[i]]]--] = id[i];
            for (int i = 1; i <= m; ++i)
                buc[i] = 0;
            rk[sa[1]] = p = 1;
            for (int i = 2; i <= n; ++i) {
                if (!eq(sa[i], sa[i - 1]))
                    ++p;
                rk[sa[i]] = p;
            }
            if (p == n)
                break;
            w <<= 1, m = p, p = 0;
        }
    }
    void build() {
        s[n + 1] = '!';
        for (int i = 1, k = 0; i <= n; ++i) {
            if (k)
                --k;
            if (rk[i] == 1)
                continue;
            while (s[i + k] == s[sa[rk[i] - 1] + k])
                ++k;
            ht[0][rk[i]] = k;
        }
        for (int t = 1; t < 21; ++t)
            for (int i = 2; i + (1 << t) - 1 <= n; ++i)
                ht[t][i] = min(ht[t - 1][i], ht[t - 1][i + (1 << (t - 1))]);
    }
    int qry(int x, int y) {
		if(y>n) return 0;
        if (x == y)
            return n - x + 1;
        x = rk[x], y = rk[y];
        if (x > y)
            swap(x, y);
        int k = __lg(y - x);
        return min(ht[k][x + 1], ht[k][y - (1 << k) + 1]);
    }
}A, B;
char s[N];
int stk[N], top;
int lin[N], nx[N*40], to[N*40], tot;
void add(int x, int y){
	nx[++tot]=lin[x]; lin[x]=tot; to[tot]=y;
}
int id[N], idx;
int nxt[N*40];
int sum[N*40];
int del[N*40];
void work(int l, int r){
	int len=r-l+1;
	int la=A.qry(l, r+1);
	int lb=B.qry(n-r+1, n-l+2);
	if(lb<len&&la+lb>=len){
        l-=lb; r+=la;
		for(int i=r-len*2; i>=l-1; --i){
			id[i]=++idx;
			add(i, id[i]);
		}
		for(int i=l+2*len-1; i<=r; ++i){
			del[id[i-2*len]]=i;
		}
		for(int i=r-len*3; i>=l-1; --i){
			nxt[id[i]]=id[i+len];
		}
	}
}
int f[N];
void solve(){
	scanf("%s", s+1); 
	n=strlen(s+1);
	// cout<<n<<endl;
	for(int i=1; i<=n; ++i){
		A.s[i]=B.s[n-i+1]=s[i]-'0'+1;
		// assert(s[i]=='0'||s[i]=='1');
		f[i]=0; lin[i]=0;
	}
	lin[0]=0;
	tot=0;
	A.getSA(); A.build();
	B.getSA(); B.build();
	top=0;
	for(int i=n; i; --i){
		while(top&&A.rk[i]>A.rk[stk[top]]){
			--top;
		}
		if(top){
			work(i, stk[top]-1);
		}
		stk[++top]=i;
	}
	top=0;
	for(int i=n; i; --i){
		while(top&&A.rk[i]<A.rk[stk[top]]){
			--top;
		}
		if(top){
			work(i, stk[top]-1);
		}
		stk[++top]=i;
	}
	f[0]=1; int tot=1;
	for(int i=lin[0], t=to[i]; i; i=nx[i], t=to[i]) {
		// cout<<"rep:"<<0<<' '<<t<<endl;
		sum[t]=(sum[t]+f[0])%mod;
		// cout<<"sum[t]:"<<sum[t]<<endl;
		if(nxt[t]){
			// cout<<"contri:"<<t<<"->"<<nxt[t]<<endl;
			sum[nxt[t]]=(sum[nxt[t]]+sum[t])%mod;
			// cout<<"after:"<<sum[nxt[t]]<<endl;
		}
		if(del[t]){
			f[del[t]]=(f[del[t]]+mod-sum[t])%mod;
		}
	}
	for(int i=1; i<=n; ++i){
		f[i]=(f[i]+tot)%mod;
		for(int j=lin[i], t=to[j]; j; j=nx[j], t=to[j]) {
			// cout<<"rep:"<<i<<' '<<t<<endl;
			sum[t]=(sum[t]+f[i])%mod;
			// cout<<"sum[t]:"<<sum[t]<<endl;
			if(nxt[t]){
				// cout<<"contri:"<<t<<"->"<<nxt[t]<<endl;
				sum[nxt[t]]=(sum[nxt[t]]+sum[t])%mod;
				// cout<<"after:"<<sum[nxt[t]]<<endl;
			}
			if(del[t]){
				f[del[t]]=(f[del[t]]+mod-sum[t])%mod;
			}
		}
		tot=(tot+f[i])%mod;
		// cout<<"f["<<i<<"]="<<f[i]<<endl;
	}
	printf("%d\n", f[n]);
	for(int i=1; i<=idx; ++i) nxt[i]=0, sum[i]=0, del[i]=0;
	idx=0;
}
int main(){
	// freopen("D:\\nya\\probs\\runs\\test.in","r",stdin);
	// freopen("D:\\nya\\probs\\runs\\test.out","w",stdout);
	read(T);
	while(T--){
		solve();
	}
	return 0;
}