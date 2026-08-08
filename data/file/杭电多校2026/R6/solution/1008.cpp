#include <bits/stdc++.h>
/*Pragma*/
/*
#pragma GCC optimize(2)
#pragma GCC optimize(3)  // »ð³µÍ·
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
*/
/*define*/
#define f(c, a, b) for (register int c = a; c <= b; c++)
#define fd(c, a, b) for (register int c = b; c >= a; c--)
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define vi vector<int>
#define int long long
#define vpii vector<pi>
#define il inline
#define ri register
#define aint(a) a.begin(), a.end()
#define fr(a) freopen(a, "r", stdin)
#define fo(a) freopen(a, "w", stdout);
#define debug puts("------------------------")
#define lowbit(x) (x & -x)
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define co const

namespace DEBUG{
	const bool DeBug=true;
	int db_cnt;
	il void db() { if (DeBug) puts("--------------"); return; }
	il void db(const auto a) { if (DeBug) ++ db_cnt, std::cerr << "-- | t" << db_cnt << " : " << a << '\n'; return; }
	il void db(const auto a, const auto b) { if (DeBug) ++ db_cnt, std::cerr << "-- | t" << db_cnt << " : " << a << ", " << b << '\n'; return; }
	il void db(const auto a, const auto b, const auto c) { if (DeBug) ++ db_cnt, std::cerr << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << '\n'; return; }
	il void db(const auto a, const auto b, const auto c, const auto d) { if (DeBug) ++ db_cnt, std::cerr << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << ", " << d << '\n'; return; }
	il void db(const auto a, const auto b, const auto c, const auto d, const auto e) { if (DeBug) ++ db_cnt, std::cerr << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << ", " << d << ", " << e << '\n'; return; }
	il void db(const auto *a, const auto len) { if (DeBug) { ++ db_cnt; std::cerr << "-- | t" << db_cnt << " : {"; if (!len) std::cerr << "empty";else { std::cerr << a[1]; for (int i = 2; i <= len; ++ i ) std::cerr << ", " << a[i]; } std::cerr << "}\n"; } return; }
	il void db(const std::pair<auto, auto> a) { if (DeBug) ++ db_cnt, std::cerr << "-- | t" << db_cnt << " : <" << a.first << ", " << a.second << ">\n"; return; }
}

namespace Functions{
	il auto Max(const auto x,const auto y){return x>y?x:y;};
	il auto toMax(auto &x,const auto y){return x=(x>y?x:y);};
	il auto Min(const auto x,const auto y){return x<y?x:y;};
	il auto toMin(auto &x,const auto y){return x=(x<y?x:y);};
	il auto Add(const auto x,const auto y){return x+y;};
	il auto toAdd(auto &x,const auto y){return x=(x+y);};
	il auto Mus(const auto x,const auto y){return x-y;};
	il auto toMus(auto &x,const auto y){return x=(x-y);};
	il auto Mul(const auto x,const auto y){return x*y;};
	il auto toMul(auto &x,const auto y){return x=(x*y);};
	il auto Mul(const auto x,const auto y,const auto p){return (x*y)%p;};
	il auto toMul(auto &x,const auto y,const auto p){return x=((x*y)%p);};
	il auto Div(const auto x,const auto y){return x/y;};
	il auto toDiv(auto &x,const auto y){return x=(x/y);};
	il int Xor(const int x,const int y){return x^y;};
	il int toXor(int &x,const int y){return x=(x^y);};
	il int And(const int x,const int y){return x&y;};
	il int toAnd(int &x,const int y){return x=(x&y);};
	il int Or(const int x,const int y){return x|y;};
	il int toOr(int &x,const int y){return x=(x|y);};
	il int popcnt(const int x){return __builtin_popcount(x);}
	il auto Sqr(const auto x){return x*x;}
	il auto toSqr(auto &x){return x=x*x;}
	il auto Sqr3(const auto x){return x*x*x;}
	il auto toSqr3(auto &x){return x=x*x*x;}
	il auto Sqr4(const auto x){return x*x*x*x;}
	il auto toSqr4(auto &x){return x=x*x*x*x;}
	il auto Sqr(auto x,int res,const int Mod){auto now=x;while(res){if(res&1) toMul(now,x);toMul(x,x);res>>=1;}return now;}
	il auto toSqr(auto x,const int res,const int Mod){return x=(Sqr(x,res,Mod));};
	il auto H_dis(const auto x,const auto y,const auto a,const auto b){return abs(x-a)+abs(y-b);}
	il auto H_dis(const std::pair<auto,auto> x,const std::pair<auto,auto> y){return H_dis(x.first,x.second,y.first,y.second);};
	il auto O_dis(auto x,auto y,auto a,auto b){return (long double)sqrt(Sqr(x-a)+Sqr(y-b));}
	il auto O_dis(const std::pair<auto,auto> x,const std::pair<auto,auto> y){return O_dis(x.first,x.second,y.first,y.second);};
}

namespace FastIO{
	il int read() {ri int ans = 0;ri char c = getchar();ri bool neg = 0;while ((c < '0') | (c > '9')) neg ^= !(c ^ '-'), c = getchar();while ((c >= '0') & (c <= '9')) ans = (ans << 3) + (ans << 1) + c - 48, c = getchar();return neg ? -ans : ans;}
	il void write(ri int x) {if (x < 0)x = -x, putchar('-');if (x > 9)write(x / 10);putchar(x % 10 + '0');}
	il void writes(ri int x) {write(x);putchar(' ');}
	il void writed(ri int x) {write(x);putchar('\n');}
}

namespace Typedef{
	typedef long double lb;
	typedef long long ll;
	typedef std::set<int>::iterator IT;
}

using namespace DEBUG;
using namespace Typedef;
using namespace FastIO;

namespace Mod{
	template<int mod>
	inline unsigned int down(unsigned int x) {
		return x >= mod ? x - mod : x;
	}
	template<int mod>
	struct Modint {
		unsigned int x;
		Modint() = default;
		Modint(unsigned int x) : x(x) {}
		friend std::istream& operator>>(std::istream& in, Modint& a) {return in >> a.x;}
		friend std::ostream& operator<<(std::ostream& out, Modint a) {return out << a.x;}
		friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
		friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
		friend Modint operator*(Modint a, Modint b) {return 1LL * a.x * b.x % mod;}
		friend Modint operator/(Modint a, Modint b) {return a * ~b;}
		friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
		friend Modint operator~(Modint a) {return a ^ (mod - 2);}
		friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
		friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
		friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
		friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
		friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
		friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
		friend Modint& operator++(Modint& a) {return a += 1;}
		friend Modint& operator--(Modint& a) {return a -= 1;}
		friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
		friend bool operator!=(Modint a, Modint b) {return !(a == b);}
		friend bool operator<(Modint a, Modint b) {return (a.x<b.x);}
		friend bool operator>(Modint a, Modint b) {return (a.x>b.x);}
	};
	typedef Modint<998244353> _int;
}

namespace Number{
	const int N = 1e6 + 3;
	int n, m;//**//
	const int INF=1e18,P=1000000007;
	const double eps=1e-6;
	int a[N];
}

/*Namespace*/

using namespace Number;
using namespace Mod;
using namespace Functions;
using namespace std;
//bccb 
int tot = 0;
inline bool check(vector<char> u, vector<char> v) {
    if (u.size() != 4 || v.size() != 4) return false;
    int perms[8][4] = {
        {0,1,2,3},  // abcd
        {3,1,2,0},  // dbca 
        {0,2,1,3},  // acbd 
        {3,2,1,0},  // dcba
        {1,0,3,2},  // badc
        {2,0,3,1},  // cadb
        {1,3,0,2},  // bdac
        {2,3,0,1}   // cdab
    };
    for (int i = 0; i < 8; i++) {
        bool flg = true;
        for (int j = 0; j < 4; j++) {
            if (v[j] != u[perms[i][j]]) {
                flg = false;
                break;
            }
        }
        if (flg){
        	 return true;
		}
    }
    return false;
}
namespace Solution{
	inline void solve(){
		n = read(); m = read();
		tot += n;
		assert(1 <= n && n <= 10000000);
		assert(1 <= m && m <= n);
		string S , T;
		cin >> S >> T;
		assert(S . size() == n); 
		assert(T . size() == n);
		vector<int> cnt(26);
		for(auto i : S) cnt[i - 'a'] ++;
		for(auto i : T) cnt[i - 'a'] --;
		f(i , 0 , 25){
			if(cnt[i] != 0) {
				puts("No"); return ;
			}
		}
		if(m == 1){
			puts("Yes"); return ;
		}
		if(n < m){
			if(S == T) puts("Yes");
			else puts("No"); return ;
		}
		if(n < 2 * m){
			if(S == T) puts("Yes");
			else{
				swap(S[0] , S[n - 1]);
				if(S == T) puts("Yes");
				else puts("No");
			}
			return ;
		}
		f(i, 1 , m - 2)
			if(S[i] != T[i])
				return puts("No") , void();
		f(i , n - m + 1 , n - 2)
			if(S[i] != T[i])
				return puts("No") , void();
		if(n - 2 * m + 4 >= 5) return puts("Yes") , void();	
		vector<char> u , v;
		u . push_back(S[0]); 
		f(i , m - 1, n - m) u . push_back(S[i]);
		u . push_back(S[n - 1]); 
		v . push_back(T[0]); 
		f(i , m - 1, n - m) v . push_back(T[i]);
		v . push_back(T[n - 1]); 	
		if(check(u , v)) return puts("Yes") , void();
		else{
			puts("No");
		}
		return;
 	}
	inline int Solve(){

		return 0;
	}
}


signed main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int T=read();

	while(T--)
	    Solution::solve();

	assert(tot <= 10000000);

	//while(T--)
	//    std::cout<<Solution::Solve()<<'\n';


    return 0;
}
