#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int N = 10;
int k, n;
vector<pair<int, int> > ans;

void Search() {
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    for (int i = 1; i <= N; i++) {
        ans.clear();
        for (int j = 1; j <= n; j++) {
            k = j, n = i;
            Search();
        }
    }
    return 0;
}
/*
*/