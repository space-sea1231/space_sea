// iro wa niohedo itsuka chiri nuruwo
// samayou koto sae yuruse nakatta
#include <bits/stdc++.h>
#define int long long
#define all(v) v.begin(),v.end()
#define fro(i,a,b) for (int i = a; i <= b; i++)
using PII = std::pair<int,int>; using std :: cerr ;
inline void chkmin (int &x , int y) { x > y && (x = y); }
inline void chkmax (int &x , int y) { x < y && (x = y); }
bool _bg_;
constexpr int inf = (sizeof (int) == 4 ? 0x3f3f3f3f : 0x3f3f3f3f3f3f3f3f);
namespace FastRead
{
	char buf[1 << 23] , *p1 = buf ,*p2 = buf;
	#define Fastest_GetChar (p1 == p2 && (p2 = (p1 = buf) + \
		fread (buf , 1 , 1 << 21 , stdin) , p1 == p2) ? EOF : *p1++)
	inline int read () 
	{
		int x = 0 , f = 1; char ch = Fastest_GetChar;
		while (!isdigit (ch)) {if (ch == '-') f = -1; ch = Fastest_GetChar;}
		while (isdigit (ch)) x = x * 10 + (ch ^ 48) , ch = Fastest_GetChar;
		return x * f;
	}
}
using FastRead :: read ;
const int N = 1e3 + 5 ;

int T ;
int n , m ;
int a[N][N] ;

inline void FakeMain ()
{
	int res = 0;
	n = read () , m = read ();
	fro (i , 0 , n + 1) fro (j , 0 , m + 1) a[i][j] = 0;
	fro (i , 1 , n) fro (j , 1 , m) a[i][j] = read ();
	fro (i , 1 , n) fro (j , 1 , m)
	{
		if (!a[i][j]) continue;
		// int lstt = res;
		if (a[i][j] == 1)
		{
			int w = 21 , now = 1;
			if (a[i - 1][j] >= 1 && a[i + 1][j] >= 1) w -= 7;
			else if (a[i - 1][j] >= 1 || a[i + 1][j] >= 1) w -= now , now++;
			if (a[i][j - 1] >= 1 && a[i][j + 1] >= 1) w -= 7;
			else if (a[i][j - 1] >= 1 || a[i][j + 1] >= 1) w -= now , now++;
			res += w;
			// cerr << res - lstt << " \n"[j == m];
			continue;
		}
		int c[] = {0 , a[i - 1][j] , a[i][j - 1] , a[i + 1][j] , a[i][j + 1] , a[i][j]};
		std :: sort (c + 1 , c + 6);
		int len = std :: unique (c + 1 , c + 6) - c;
		// cerr << len << " " << a[i][j] << "\n";
		int lst = 0 , fir = -1;
		for (int k = 1; k < len; k++)
		{
			int w = 14 , now = 1;
			if (a[i - 1][j] >= c[k] && a[i + 1][j] >= c[k]) w -= 7;
			else if (a[i - 1][j] >= c[k] || a[i + 1][j] >= c[k]) w -= now , now++;
			if (a[i][j - 1] >= c[k] && a[i][j + 1] >= c[k]) w -= 7;
			else if (a[i][j - 1] >= c[k] || a[i][j + 1] >= c[k]) w -= now , now++;

			res += w * (c[k] - c[k - 1]);
			// if (i == 2 && j == 2) cerr << c[k] << " " << w << " | " << w * (c[k] - c[k - 1]) << "\n";
			lst = w;
			if (fir == -1 && c[k] - c[k - 1] > 0) fir = w;
			if (c[k] == a[i][j]) break;
		}
		res -= lst;
		if (fir != -1) res -= fir;
		// if (i == 2 && j == 2) cerr << res - lstt << "\n";
		

		int w = 21 , now = 1;
		res-- , now++;
		if (a[i - 1][j] >= a[i][j] && a[i + 1][j] >= a[i][j]) w -= 7;
		else if (a[i - 1][j] >= a[i][j] || a[i + 1][j] >= a[i][j]) w -= now , now++;
		if (a[i][j - 1] >= a[i][j] && a[i][j + 1] >= a[i][j]) w -= 7;
		else if (a[i][j - 1] >= a[i][j] || a[i][j + 1] >= a[i][j]) w -= now , now++;
		res += w;

		w = 21 , now = 1;
		res-- , now++;
		if (a[i - 1][j] >= 1 && a[i + 1][j] >= 1) w -= 7;
		else if (a[i - 1][j] >= 1 || a[i + 1][j] >= 1) w -= now , now++;
		if (a[i][j - 1] >= 1 && a[i][j + 1] >= 1) w -= 7;
		else if (a[i][j - 1] >= 1 || a[i][j + 1] >= 1) w -= now , now++;
		res += w;
		// cerr << res - lstt << " \n"[j == m];
	}

	// cerr << "----------------------------\n";

	std :: cout << res << "\n";
}

bool _ed_;
signed main ()
{
	for (T = read (); T -- ; FakeMain ());
	
	cerr << "\nTime: " << clock () * 1.0 / CLOCKS_PER_SEC << "s\n";
	cerr << "Memory: " << fabs (&_bg_ - &_ed_) / 1024. / 1024. << "Mib\n";
	return 0;
}