/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<string>
#define int long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 1e5+5;
const int INF = 1e9+7;
const int mod = 1e9+7;
const int Max = 1e9;

int n, m;
int root[MAXN];

int read(){
	int s = 0, f = 0;
	char ch = getchar();
	while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
	return f ? -s : s;
}

namespace Hjt {
    #define ls lson[now_]
    #define rs rson[now_]
    int lson[MAXN << 5], rson[MAXN << 5], val[MAXN << 5], node_num = 0;
    void Insert(int &now_, int pre_, int l, int r, int pos, int val_) {
        now_ = ++ node_num;
        val[now_] = val[pre_] + val_; 
        ls = lson[pre_], rs = rson[pre_];
        if(l == r) return ;
        int mid = (l + r) >> 1;
        if(pos <= mid) Insert(ls, lson[pre_], l, mid, pos, val_);
        else Insert(rs, rson[pre_], mid + 1, r, pos, val_);
    }
    int Query(int now_, int pre_, int l, int r, int L, int R) {
        if(!(val[now_] - val[pre_])) return 0;
        if(L <= l && r <= R) return val[now_] - val[pre_];
        int mid = (l + r) >> 1, res = 0;
        if(mid >= L) res += Query(ls, lson[pre_], l, mid, L, R);
        if(mid < R) res += Query(rs, rson[pre_], mid + 1, r, L, R);
        return res;
    }
}

signed main()
{
    n = read();
    for(int i = 1, x; i <= n; ++i) {
        x = read();
        Hjt::Insert(root[i], root[i - 1], 1, Max, x, x);
    }
    m = read();
    for(int i = 1, l, r; i <= m; ++i) {
       l = read(), r = read();
       int lst = 0, now = 0;
       while(1 + 2 == 3) {
           int tmp = Hjt::Query(root[r], root[l - 1], 1, Max, lst + 1, now + 1);
//           cout<<"tmp: "<<tmp<<"\n";
           if(tmp) lst = now + 1, now += tmp;
           else break;
       }
       printf("%lld\n", now + 1);
    }
	return 0;
}
