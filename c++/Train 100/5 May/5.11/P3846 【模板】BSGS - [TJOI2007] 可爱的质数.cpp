#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug
#define int long long

using namespace std;
typedef long long ll;

const int N = 5e4 + 10;

struct Tmp {
    int val;
    int pos;
    
    bool operator < (const Tmp src) const {
        return val < src.val;
    }
    bool operator == (const Tmp& src) const {  
        return val == src.val;
    }
};

Tmp tmp[N];
int top;
int p, a, b;

int Pow(int a, int b, int p) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = ((ll)sum * a) % p;
        a = ((ll)a * a) % p;
        b >>= 1;
    }
    return sum;
}

int BSGS(int p, int a, int b) {
    a = a % p, b = b % p;
    if (b == 1) return 0;
    if (a == 0) return (b == 0) ? 1 : -1;
    int siz = sqrt(p) + 1;
    for (int i = 0; i < siz; i++) {
        tmp[i + 1].val = (ll)b * Pow(a, i, p) % p;
        tmp[i + 1].pos = i;
    }
    sort(tmp + 1, tmp + siz + 1);
    int len = unique(tmp + 1, tmp + siz + 1) - tmp - 1;
    int A = Pow(a, siz, p);
    a = 1;
    for (int i = 1; i <= siz; i++) {
        a = (ll)a * A % p;
        int l = 1, r = len;
        while (l < r) {
            int mid = (l + r) / 2;
            if (tmp[mid].val >= a) r = mid;
            else l = mid + 1;
        }
        if (tmp[l].val == a) return i * siz - tmp[l].pos;
    }
    return -1;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> p >> a >> b;
    int res = BSGS(p, a, b);
    if (res == -1) printf("no solution\n");
    else printf("%d\n", res);
    return 0;
}