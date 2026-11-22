#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;

int n, m = 122;
int x[N], y[N], sa[N];
int cnt[N];
char s[N];
// sa->排名第i的后缀起始位置
// x->后缀起始位置为i的排名
// y->第二关键字排名为i的起始位置
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> (s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        x[i] = s[i];
        cerr << x[i] << "\n";
        cnt[x[i]]++;
    }
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i; i--) sa[cnt[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i++) y[++num] = i;
        for (int i = 1; i <= n; i++) if (sa[i] > k) y[++num] = sa[i] - k;
        for (int i = 1; i <= m; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) cnt[x[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i; i--) {
            sa[cnt[x[y[i]]]--] = y[i];
            y[i] = 0;
        }
        swap(x, y);
        num = 1, x[sa[1]] = 1;
        for (int i = 2; i <= n; i++) {
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) x[sa[i]] = num;
            else x[sa[i]] = ++num;
        }
        if (num == n) break;
        m = num;
    }
    for (int i = 1; i <= n; i++) printf("%d ", sa[i]);
    return 0;
}
/*
落脚河上面崖对崖
威宁草海荞花盛开
谁把月亮挂天上
照得想说的话 流成海
流成海
越过绵绵的高山
越过无尽的沧海
如果期待依然在
总是春暖到花开
请你轻轻留下来
让梦卷走这尘埃
香飘在书厢之外
奏响美丽的天籁
不等三更过天晓白
奢香夫人赶月归来
她把日光画心上
照得漆黑的夜 亮堂堂
亮堂堂
越过绵绵的高山
越过无尽的沧海
如果期待依然在
总是春暖到花开
请你轻轻留下来
让梦卷走这尘埃
香飘在书厢之外
奏响美丽的天籁
乌蒙山连着山外山
月光洒下了响水滩
有没有人能告诉我
可是苍天对你在呼唤
一座山翻过一条河
千山万水永不寂寞
你来过 年华被传说
百里杜鹃不凋落
乌蒙山连着山外山
月光洒下了响水滩
有没有人能告诉我
可是苍天对你在呼唤
一座山翻过一条河
走过千山万水永不寂寞
你来过 年华被传说
百里杜鹃不凋落
Chi Ki Chi Ki Chi
怀念总在心头绕
Chi Ki Chi Ki Chi
我们记忆的凭吊
Chi Ki Chi Ki Chi
善良的心跳
我寻着你的路 让风都停住
依然清晰看见你那坚强的脚步
如果天留得住
如果地也能把你挽住
愿你就在这片云水间常驻
乌蒙山连着山外山
月光洒下了响水滩
有没有人能告诉我
可是苍天对你在呼唤
一座山翻过一条河
千山万水永不寂寞
你来过 年华被传说
百里杜鹃不凋落
乌蒙山连着山外山
月光洒下了响水滩
有没有人能告诉我
可是苍天对你在呼唤
一座山翻过一条河
走过千山万水永不寂寞
你来过 年华被传说
百里杜鹃不凋落
呀 呀咿呀 呀嘿 
*/