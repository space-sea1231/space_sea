#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int a[2];
int num;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    a[++num] = 2, a[num] = 1;
	cerr << a[0] << " " << a[1] << "\n";
    return 0;
}