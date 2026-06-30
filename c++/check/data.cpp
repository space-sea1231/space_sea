#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
typedef long long ll;

int n = 20;

int Random(int l, int r) {
    return (long long)rand() * rand() % (r - l + 1) + l;
}

int main() {
    srand((unsigned)time(0));
    printf("%d\n", n);
    for (int i = 1; i <= n; i++) {
        printf("%d\n", i);
    }
    return 0;
}