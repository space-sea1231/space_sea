#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define eb emplace_back
#define lfor(i, x, y) for (int i = (x); i <= (y); ++ i)
#define llfor(i, x, y) for (int i = (x); i < (y); ++ i)
#define rfor(i, x, y) for (int i = (x); i >= (y); -- i)
#define rlfor(i, x, y) for (int i = (x); i > (y); -- i)
#define For(i, p) for(int i = G.head[p]; ~i; i = G.nxt[i])
template <typename T>inline void read(T &x){bool f=0;x=0;char ch=getchar();while ((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-')ch=getchar(),f=1;while (ch>='0' && ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}x=f?-x:x;}
template <typename T1,typename... T2>inline void read(T1 &x,T2& ...y){read(x);read(y...);}
#define int long long 
/*======================Header Template======================*/
auto pii = [](int x, int y) { return std::make_pair(x, y); }; 
typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int, int> pr;
typedef tuple<int, int, int> tpl;
const int N = 4e5 + 5;
const int M = 4e5; 
struct PT {
  ll fi, se, id; 
}; 
struct BIT {
  int tr[M + 5], n;
  void init(int x) {n = x; lfor(i, 1, x) tr[i] = 0; }
  void add(int pos, int val) {
    for(; pos <= n; pos += pos & -pos) tr[pos] += val;
  }
  int ask(int pos) {
    int ret = 0; 
    for(; pos; pos -= pos & -pos) ret += tr[pos];
    return ret; 
  }
} T; 
ll a[N], X[N], Y[N];

ll gp(ll val, int pos) {
  return val * (a[pos + 1] + a[pos - 1]);
} 

bool cmp(PT x, PT y) {
  return x.fi < y.fi; 
}

void work() {
  int n; cin >> n;
  lfor(i, 1, n) cin >> a[i];
  if (n <= 2) {cout << "0" << endl; return; }
  ll fA = 0, ans = 0;
  lfor(i, 1, n - 1) fA += (a[i] - a[i + 1]) * (a[i] - a[i + 1]);  
  if (a[1] * a[1] - a[2] * a[2] - 2 * a[1] * a[3] + 2 * a[2] * a[3] > 0) ++ ans; 
  lfor(i, 3, n - 1) {
    ll f1 = a[1] * a[1] - a[i] * a[i] - 2 * a[2] * (a[i] - a[1]) - 2 * gp(a[1], i) + 2 * gp(a[i], i);
    if (f1 > 0) ++ ans; 
  }
  if (a[n] * a[n] - a[n - 1] * a[n - 1] - 2 * a[n] * a[n - 2] + 2 * a[n - 1] * a[n - 2] > 0) ++ ans; 
  rfor(i, n - 2, 2) {
    ll fn = a[n] * a[n] - a[i] * a[i] - 2 * a[n - 1] * (a[i] - a[n]) - 2 * gp(a[n], i) + 2 * gp(a[i], i);
    if (fn > 0) ++ ans; 
  }
  {
    ll st1 = a[1] * a[2] + a[n - 1] * a[n];
    ll st2 = a[n] * a[2] + a[n - 1] * a[1];
    if (st2 < st1) ++ ans;  
  }
  lfor(i, 2, n - 2) {
    ll D = (a[i - 1] - a[i + 2]) * (a[i] - a[i + 1]);
    if (D > 0) ++ ans;  
  }
  vector<PT> pt; 
  lfor(i, 2, n - 1) {
    PT elm = {a[i], a[i - 1] + a[i + 1], i};
    X[i] = a[i];
    Y[i] = a[i - 1] + a[i + 1]; 
    pt.eb(elm);
  }
  sort(pt.begin(), pt.end(), cmp); 

  T.n = M; 
  int siz = pt.size(); 
  llfor(i, 0, siz) {
    int j = i;
   while (j < siz && pt[j].fi == pt[i].fi) ++ j; 
   llfor(k, i, j) {
    ans += T.ask(pt[k].se - 1); 
    int id = pt[k].id, x = pt[k].fi, y = pt[k].se;
    for(int nb : {id - 1, id + 1}) {
      if (2 <= nb && nb <= n - 1 && X[nb] < x && Y[nb] < y) -- ans;  
    }
   }
   llfor(k, i, j) T.add(pt[k].se, 1); 
   i = j - 1;
  }
  for(auto [x, y, id] : pt) T.add(y, - 1); 

  cout << ans << endl; 
}

signed main() {
	ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int Test = 1; cin >> Test; 
  lfor(i, 1, Test) work(); 
	return 0;
}