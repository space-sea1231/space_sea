#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n;
int a[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    int flag = -1, ans = 1, lst = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (i == 1) { lst = x; continue;}
        if (x > lst && flag != 1) {
            flag = 1;
            ans++;
        } else if (x < lst && flag){
            flag = 0;
            ans++;
        }
        lst = x;
    }
    printf("%d\n", ans);
    
    return 0;
}
/*
Small steps,taken daily,become a long road traveled.
每天一小步，走过的就是长路。
*/