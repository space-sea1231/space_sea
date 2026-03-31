#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    int a, b;
    cin >> a >> b;
    if (a >= 4 || b == 0) printf("No\n");
    else printf("Yes\n");
    return 0;
}